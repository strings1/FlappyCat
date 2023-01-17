
#include "Gameloop.h"
#include "Definers.h"
#include <cstring>
#include <fstream>
#include <string.h>
 
using namespace std;
static bool started = false;
static bool inShop = false;
block logo(0,0,500,250,SCREEN_W/2-(LogoSize_W/2),SCREEN_H/6,LogoSize_W,LogoSize_H);
block unlocked(0, 0, 32, 32, 0, 0, 300, 300);
block locked(0, 0, 32, 32, 0, 0, 300, 300);
block selected(0, 0, 64, 32, 0, 0, 0, 0);

block quinn(0,0,40,64,0,0,80,128);
block eevee(0,0,30,64,0,0,80,128);
block elgato(0,0,30,64,0,0,80,128);
block coolelgato(0, 0, 30, 64, 0, 0, 80, 128);

SDL_Color color = { 167, 3, 255 };
TEXT ScoreText(color,25);

//BUTOANELE:
Button start_button(0, 0, 32, 32,
                    SCREEN_W/2-ButtonSize/2,SCREEN_H/2 + ButtonSize/2, 
                    ButtonSize, ButtonSize);
Button retry_button(0, 0, 32, 32, start_button.get_dest().x, SCREEN_H,
    ButtonSize, ButtonSize);

Button cosmetic_button(0, 0, 32, 32,
                    start_button.get_dest().x-(ButtonSize+50),start_button.get_dest().y, 
                    ButtonSize, ButtonSize);//OFFSET 50 STG

Button back_button(0, 0, 32, 32, 20, SCREEN_H-ButtonSize/2-50, ButtonSize/2, ButtonSize/2);

Button arrowL_button(0,0,32,32
    ,start_button.get_dest().x-2*ButtonSize,start_button.get_dest().y,
    ButtonSize, ButtonSize);

Button arrowR_button(0,0,32,32
    ,start_button.get_dest().x+2*ButtonSize,start_button.get_dest().y,
    ButtonSize, ButtonSize);

Button buy_button(0, 0, 64, 32, (arrowL_button.get_dest().x+ButtonSize+ButtonSize/2), arrowL_button.get_dest().y, ButtonSize * 2, ButtonSize);
Button pick_button(0, 0, 64, 32, (arrowL_button.get_dest().x+ButtonSize+ButtonSize/2), arrowL_button.get_dest().y, ButtonSize * 2, ButtonSize);

switching_button difficulty(0,0,38,38, start_button.get_dest().x + (ButtonSize + 50), start_button.get_dest().y,
    ButtonSize, ButtonSize,3);// OFFSET 50 dreapta

//-------------------------------------------


Catalog<item> catalog_pisici("prop/catalog_prop.txt");
size_t nr_dogs_byDifficulty = 3 + 3 * difficulty.timesclicked() % difficulty.get_nr_buttons();


static bool spacePressed = false;
static bool click = false;

static enemy dogs[num_of_dogs];
static Coin coin[num_of_coins];
static Pwr_Mul coinmul;
static size_t i;
size_t maxnum = (num_of_coins > num_of_dogs) ? num_of_coins : num_of_dogs;
GameLoop::GameLoop()
{
	_window = NULL;
	_renderer = NULL;
	_GameState = NOT_RUNNING;
    playr.setSource(0, 0, 254, 541);
    playr.setDest(200, 200, PLAYER_W, PLAYER_H);
    //bg 1- constructor
    bg2.setDest(bg1.get_dest().x + bg1.get_dest().w, 0, SCREEN_W, SCREEN_H);

}

void GameLoop::SaveProgress(const char* scoretxt, const char* catalogtxt)
{
    cout << "\nSalvez progresul...\n";
    FILE* Score_File_out = nullptr;
    fopen_s(&Score_File_out, scoretxt, "w");
    if (Score_File_out)
    {    fprintf(Score_File_out, "%d", playr.GetScore());
    fclose(Score_File_out);
        cout << "Am salvat scorul cu succes!\n";
    }

    ofstream catalog_out;
    catalog_out.open(catalogtxt);
    if (catalog_out.good())
    {
        catalog_out << catalog_pisici.getsize()<<endl;
        for (i = 0; i < catalog_pisici.getsize(); i++)
            catalog_out << ~*catalog_pisici[i]<<" ";
        cout << "Am salvat catalogul cu succes!\n";
    }

    catalog_out.close();
}

void GameLoop::Initialize() {
	SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
	_window = SDL_CreateWindow("Flappy Cat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, 0);
	if (_window) {

		_renderer = SDL_CreateRenderer(_window, -1, 0);
		if (_renderer) {

            cout << "Initializare texturi...\n";
            //TEXT:
            ScoreText.initialize("FFFFORWA.ttf");
            ScoreText.setText(_renderer, "Scorul tau este: ");

            //Essential STUFF----------------------------
            playr.CreateTexture("Sprites/pixeevee.png", _renderer);
            bg1.CreateTexture("Sprites/background.png", _renderer);
            bg2.CreateTexture("Sprites/background.png", _renderer);
            logo.CreateTexture("Sprites/logo.png", _renderer);
            selected.CreateTexture("Sprites/selected.png", _renderer);

            //BUTOANE:
            start_button.LoadTextures(_renderer, "Sprites/playbutton.png", "Sprites/h_playbutton.png", "Sprites/p_playbutton.png");
            cosmetic_button.LoadTextures(_renderer, "Sprites/cosmetic.png", "Sprites/h_cosmetic.png", "Sprites/p_cosmetic.png");
            back_button.LoadTextures(_renderer, "Sprites/back.png", "Sprites/h_back.png", "Sprites/p_back.png");
            arrowL_button.LoadTextures(_renderer, "Sprites/leftarrow.png", "Sprites/h_leftarrow.png", "Sprites/p_leftarrow.png");
            arrowR_button.LoadTextures(_renderer, "Sprites/rightarrow.png", "Sprites/h_rightarrow.png", "Sprites/p_rightarrow.png");
            buy_button.LoadTextures(_renderer, "Sprites/buy.png", "Sprites/h_buy.png", "Sprites/p_buy.png");
            pick_button.LoadTextures(_renderer, "Sprites/pick.png", "Sprites/h_pick.png", "Sprites/p_pick.png");
            retry_button.LoadTextures(_renderer, "Sprites/retry.png", "Sprites/h_retry.png", "Sprites/p_retry.png");
            
            
            difficulty.load_button_i(1, _renderer, "Sprites/pixmedium.png", "Sprites/h_pixmedium.png", "Sprites/p_pixmedium.png");
            difficulty.load_button_i(2, _renderer, "Sprites/pixdemon.png", "Sprites/h_pixdemon.png", "Sprites/p_pixdemon.png");
            difficulty.load_button_i(0, _renderer, "Sprites/easy.png", "Sprites/h_easy.png", "Sprites/p_easy.png");
           
            //FONT:

            //MOVING STUFF
            coinmul.LoadFrames(_renderer);
            for(i=0;i< maxnum;i++)
            {   
                if(i<num_of_dogs)
                    dogs[i].CreateTexture("Sprites/pixenemy.png", _renderer);
                if (i < num_of_coins)
                    coin[i].LoadFrames(_renderer); 
            }

            //SHOP
            unlocked.CreateTexture("Sprites/unlocked.png", _renderer);
            locked.CreateTexture("Sprites/locked.png", _renderer);

            quinn.CreateTexture("Sprites/pixquinn.png", _renderer);

            eevee.CreateTexture("Sprites/pixeevee.png", _renderer);

            elgato.CreateTexture("Sprites/pixelgato.png", _renderer);

            coolelgato.CreateTexture("Sprites/pixelgatocool.png", _renderer);
            //--------------

            //background = TextureManager::Texture("Sprites/background.png",_renderer);
            _GameState = RUNNING;
            cout << "Initializez valorile din shop...\n";
            InitShopValues(catalog_pisici);
            cout << "INITIALIZARE REALIZATA CU SUCCES!\n";
		}
		else cout << "NU AM PUTUT CREA RENDERERUL!" << SDL_GetError();
	}
	else {
		cout << "NU AM PUTUT CREA WINDOW!" << SDL_GetError();
	}
}

void GameLoop::Render(void) //Daca avem animatii, trebuie sa dam clear si dupa sa randam inapoi
{
	SDL_RenderClear(_renderer);
    bg1.Render(_renderer, *bg1.get_texture(),bg1.get_src(),bg1.get_dest());
    bg2.Render(_renderer, *bg2.get_texture(), bg2.get_src(), bg2.get_dest());

    if (started) {
        coinmul.Render(_renderer, *coinmul.get_texture(), coinmul.get_src(), coinmul.get_dest());
        playr.Render(_renderer, *playr.get_texture(), playr.get_src(), playr.get_dest());
        for (i = 0; i < maxnum; i++)
        {
            if (i < num_of_dogs)
                dogs[i].Render(_renderer, *dogs[i].get_texture(), dogs[i].get_src(), dogs[i].get_dest());
            if (i < num_of_coins)
                coin[i].Render(_renderer, *coin[i].get_texture(), coin[i].get_src(), coin[i].get_dest());
        }
        if (!playr.isAlive())
        {
            Retry();
        }
    }
    else Menu();

	SDL_RenderPresent(_renderer);
}

void GameLoop::Clear()
{
    //Se sterge mai intai rendererul si dupa nu mai pot sa sterg texturile??
    //This is a fix I think. not sure;
    size_t i;

    //Text:
    ScoreText.destroy();
    //blocks:
    SDL_DestroyTexture(*eevee.get_texture());
    SDL_DestroyTexture(*quinn.get_texture());
    SDL_DestroyTexture(*elgato.get_texture());
    SDL_DestroyTexture(*logo.get_texture());
    SDL_DestroyTexture(*unlocked.get_texture());
    SDL_DestroyTexture(*locked.get_texture());
    SDL_DestroyTexture(*selected.get_texture());

    //Buttons:
    arrowL_button.DestroyTex();
    arrowR_button.DestroyTex();
    back_button.DestroyTex();
    buy_button.DestroyTex();
    pick_button.DestroyTex();
    start_button.DestroyTex();
    cosmetic_button.DestroyTex();
    retry_button.DestroyTex();

    //Entities & Player
    SDL_DestroyTexture(*playr.get_texture());
    for (i = 0; i < maxnum; i++)
    {
        if (i < num_of_dogs)
            SDL_DestroyTexture(*dogs[i].get_texture());
        if (i < num_of_coins)
            coin[i].DestroyTex();
    }
    coinmul.DestroyTex();

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

void GameLoop::Event()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            _GameState = NOT_RUNNING;
            break;

            // check for keypresses
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
            case SDLK_UP:
                spacePressed = true;
                break;
            case SDLK_ESCAPE:
                _GameState = NOT_RUNNING;
                break;
            default:
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                case SDLK_UP:
                    spacePressed = false;
                break;
            default:
                break;
            }
            break;

        //case SDL_MOUSEMOTION:
        //      cout << event.motion.x , y;
        case SDL_MOUSEBUTTONDOWN:
        {
            click = true;
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            click = false;
            break;
        }
        default:break;
    }

    check_for_collision(dogs, &playr, coin, &coinmul);
}

void GameLoop::Update()
{
    bg1.Update();
    bg2.Update();
    if (started)
    {
        if (playr.isAlive())
        {

            coinmul.Update();
            for (i = 0; i < maxnum; i++)
            {
                if (i < nr_dogs_byDifficulty)
                    dogs[i].Update(dogs, i);
                if (i < num_of_coins)
                    coin[i].Update();
            }

        }
        //if not change to low speed
    playr.Update(spacePressed);
    }




   // cout <<"SCORE: "<< playr.GetScore() << endl;


    //playr.gravity();
}

void GameLoop::Menu()
{
    if (!inShop)
    {
        logo.Render(_renderer, *logo.get_texture(), logo.get_src(), logo.get_dest());
        start_button.Render(_renderer, click);
        cosmetic_button.Render(_renderer, click);
        difficulty.Render(_renderer, click);
        if(difficulty.clicked())
        {
            nr_dogs_byDifficulty = 2 + 2 * (difficulty.timesclicked() % difficulty.get_nr_buttons());
            cout << "O sa spawnez " << nr_dogs_byDifficulty << " Caini!\n";
            maxnum = (num_of_coins > nr_dogs_byDifficulty) ? num_of_coins : nr_dogs_byDifficulty;
            for (size_t i = 0; i < num_of_dogs; i++)
                dogs[i].setdest_x(-Enemy_W);
        }
        if (start_button.clicked())
        {
            started = true;
            playr.setgodmode(true);
            playr.respawn();
            playr.godtime_s = SDL_GetTicks64();
        }

        if (cosmetic_button.clicked())
        {
            inShop = true;
        }
    }

    if (inShop)
    {
        Shop(); //Am scris "Shop" atat de mult incat acum mi se pare ciudat cuvantul
    }

}

void GameLoop::Retry()
{
    if (playr.get_dest().y >= SCREEN_H)//Daca a terminat de cazut
    {
        retry_button.Render(_renderer,click);
        if ((retry_button.get_dest().y >= start_button.get_dest().y))
            retry_button.setDest(start_button.get_dest().x, retry_button.get_dest().y-10, retry_button.get_dest().w, retry_button.get_dest().h);
        else
            if (retry_button.clicked())
            {
                retry_button.setDest(start_button.get_dest().x, SCREEN_H, retry_button.get_dest().w, retry_button.get_dest().h);
                playr.respawn();
                playr.resetJGAA();
                for (size_t i = 0; i < maxnum; i++)
                {
                    if (i < num_of_dogs)
                        dogs[i].setdest_x(-Enemy_WD);
                    if (i < num_of_coins)
                        coin[i].setdest_x(-COIN_SIZE);
                }
                coinmul.setdest_x(-coinmul.get_dest().w);
                playr.setdest_y(200);
                coinmul.reset_mul();
                playr.setgodmode(true);
                playr.godtime_s = SDL_GetTicks64();
            }
        back_button.Render(_renderer, click);
        if (back_button.clicked())
        {
            inShop = false;
            started = false;
            playr.respawn();
            playr.resetJGAA();
            for (size_t i = 0; i < maxnum; i++)
            {
                if (i < num_of_dogs)
                    dogs[i].setdest_x(-Enemy_W);
                if (i < num_of_coins)
                    coin[i].setdest_x(-COIN_SIZE);
            }
            coinmul.setdest_x(-coinmul.get_dest().w);
            playr.setdest_y(200);
            coinmul.reset_mul();
        }
    }

}

void GameLoop::InitShopValues(Catalog<item>& p)
{
    for (i = 0; i < p.getsize(); i++)
    {
        p[i]->setprice(200*(i+1));
        p[i]->setSource(0, 0, 30, 64);
        p[i]->setDest(0, 0, 60, 128);
    }
    p[0]->setTex(eevee.get_texture());
    p[1]->setTex(quinn.get_texture());
    p[1]->setSource(0, 0, 40, 64);
    p[2]->setTex(elgato.get_texture());
    p[3]->setTex(coolelgato.get_texture());
}

void GameLoop::Shop()
{
    char text[100];
    int left, center, right; //Daca scad o valoare din unsigned, nu se duce pe 0xFFFFFFFFFF..
    SDL_Rect temp;
    //item* temp;
    block Cblock(0, 0, 600, 600, buy_button.get_dest().x, logo.get_dest().y, ButtonSize*2, ButtonSize*2);
    block Lblock(0, 0,600,600,Cblock.get_dest().x-10-Cblock.get_dest().w, Cblock.get_dest().y, ButtonSize * 2, ButtonSize * 2);
    block Rblock(0, 0, 600, 600, Cblock.get_dest().x +10+Cblock.get_dest().w, Cblock.get_dest().y, ButtonSize * 2, ButtonSize * 2);
    left = catalog_pisici.left;
    center = catalog_pisici.center;
    right = catalog_pisici.right;
    //MARIM PISICILE SA FIE MAI CLARE!
    catalog_pisici[center]->setDest(0,0, catalog_pisici[center]->get_dest().w<<1, catalog_pisici[center]->get_dest().h<<1);
    catalog_pisici[center]->Center(Cblock.get_dest());

    catalog_pisici[left]->setDest(0,0, catalog_pisici[left]->get_dest().w<<1, catalog_pisici[left]->get_dest().h<<1);
    catalog_pisici[left]->Center(Lblock.get_dest());

    catalog_pisici[right]->setDest(0,0, catalog_pisici[right]->get_dest().w<<1, catalog_pisici[right]->get_dest().h<<1);
    catalog_pisici[right]->Center(Rblock.get_dest());



    //Rendering part:

    back_button.Render(_renderer,click);
    arrowL_button.Render(_renderer, click);
    arrowR_button.Render(_renderer, click);
    if(~*catalog_pisici[center]) //if unlocked
        pick_button.Render(_renderer, click);
    else
        buy_button.Render(_renderer, click);


    //! return price
    //~ return status   0 locked      1 unlocked
    //++ unlocked +return
    //-- locked +return
    if (~*catalog_pisici[left])
    {
        Lblock.setTex(unlocked.get_texture());
    }
    else Lblock.setTex(locked.get_texture());

    if (~*catalog_pisici[center])
    {
        Cblock.setTex(unlocked.get_texture());
    }
    else Cblock.setTex(locked.get_texture());

    if (~*catalog_pisici[right])
    {
        Rblock.setTex(unlocked.get_texture());
    }
    else Rblock.setTex(locked.get_texture());

        

    Rblock.Render(_renderer, *Rblock.get_texture(), Rblock.get_src(), Rblock.get_dest());
    Lblock.Render(_renderer, *Lblock.get_texture(), Lblock.get_src(), Lblock.get_dest());
    Cblock.Render(_renderer, *Cblock.get_texture(), Cblock.get_src(), Cblock.get_dest());

    catalog_pisici[center]->Render(_renderer, *catalog_pisici[center]->get_texture(), catalog_pisici[center]->get_src(), catalog_pisici[center]->get_dest());
    catalog_pisici[left]->Render(_renderer, *catalog_pisici[left]->get_texture(), catalog_pisici[left]->get_src(), catalog_pisici[left]->get_dest());
    catalog_pisici[right]->Render(_renderer, *catalog_pisici[right]->get_texture(), catalog_pisici[right]->get_src(), catalog_pisici[right]->get_dest());
   
    //Resize them back
    catalog_pisici[left]->setDest(0, 0, catalog_pisici[left]->get_dest().w >> 1, catalog_pisici[left]->get_dest().h >> 1);
    catalog_pisici[center]->setDest(0, 0, catalog_pisici[center]->get_dest().w >> 1, catalog_pisici[center]->get_dest().h >> 1);
    catalog_pisici[right]->setDest(0, 0, catalog_pisici[right]->get_dest().w >> 1, catalog_pisici[right]->get_dest().h >> 1);
    //Logic part:
    if (back_button.clicked())
    {
        inShop = false;
        return;
    }

    if (buy_button.clicked() && !~*catalog_pisici[center])
    {
        if ((playr.GetScore() > !*catalog_pisici[center]))
        {
            (*catalog_pisici[center])++;
            playr.SetScore(playr.GetScore() - !*catalog_pisici[center]);
        }
    }

    if (pick_button.clicked() && ~*catalog_pisici[center])
    {
        if (playr.setTex(catalog_pisici[center]->get_texture()))
        {
            cout << "Diferite!\n"; //PT DEBUG
        }
        else 
        playr.setDest(200, 200, catalog_pisici[center]->get_dest().w, catalog_pisici[center]->get_dest().h);
    }
    

    if (arrowL_button.clicked())
    {
        left--; 
        center--;
        right--; //Aici e problema, cand se face -- pt ca e posibil sa faca 0-1

        //L C R
        //0 1 2
        //2 0 1
        //1 2 0
        // 
        //0 1 2 3
        //3 0 1 2
        //2 3 0 1
        //1 2 3 0
        
        //0 1 2 3 4
        //4 0 1 2 3
        //3 4 0 1 2
        //2 3 4 0 1
        //1 2 3 4 0
        if (left < 0)
        {
            left = catalog_pisici.getsize()-1;// catalog_pisici.getsize()-1;
            right = catalog_pisici.center;
            center = 0;
            //cout << "LEFT<0";
        }
        else
        {
            if (center < 0)
            {
                center = catalog_pisici.getsize() - 1;
                //cout << "CENTER<0";
            }
            else
            {
                if (right < 0)
                {
                    right = catalog_pisici.getsize() - 1;
                    center = right-1;
                    left = center - 1;
                    //cout << "RIGHT<0";
                }
            }
        }
    }

    if (arrowR_button.clicked())
    {
        left++;
        right++;
        center++;
    }

    if (*playr.get_texture() == *catalog_pisici[center]->get_texture())
    {
        selected.setDest(pick_button.get_dest().x, pick_button.get_dest().y, pick_button.get_dest().w, pick_button.get_dest().h);
        selected.Render(_renderer, *selected.get_texture(), selected.get_src(), selected.get_dest());
    }

    
    catalog_pisici.left = left % catalog_pisici.getsize();
    catalog_pisici.right = right % catalog_pisici.getsize();
    catalog_pisici.center = center % catalog_pisici.getsize();

    strcpy_s(text,100, "Scorul tau este: ");
    char* scrtext = new char[100];
    _itoa_s(playr.GetScore(), scrtext,100, 10);
    strcat_s(text, 100,scrtext );
    ScoreText.setText(_renderer, text);
    free(scrtext);
    ScoreText.Render(_renderer);
    //cout << left << " " << center << " " << right << endl;

}
