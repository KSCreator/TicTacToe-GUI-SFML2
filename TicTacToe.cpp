////////////////////////////////
/**Author   - Keshav Sahu
*  Version - 1.0
*  This is made using SFML2 library
*//////////////////////////////

#include <SFML\Graphics.hpp>

/// Pixel size of Image     ///
#define PixelSize 150

///    Define player type   ///
#define PNONE 0
#define PlayerO 1
#define PlayerX 2

///   To check if match is won by any player or not ///
int getWinner(unsigned short int data[3][3])
{
    for(int k = 0; k < 3; k++)
    {
            ///    Check row wise                 ///
        if(data[0][k] != PNONE and (data[0][k] == data[1][k] and data[1][k] == data[2][k]))
            return data[0][k];
            ///    Check column wise              ///
        if(data[k][0] != PNONE and (data[k][0] == data[k][1] and data[k][1] == data[k][2]))
            return data[k][0];
    }
    if(data[1][1] != PNONE)
    {
            ///    Check top-left to bottom-right ///
        if(data[0][0] == data[1][1] and data[1][1] == data[2][2])
            return data[0][0];
            ///    Check top-right to bottom-left ///
        else if(data[0][2] == data[1][1] and data[1][1] == data[2][0])
            return data[0][2];
    }
    /// If no player won then return none   ///
    return PNONE;
}

int main()
{
    ///   Image Texture and Sprite    ///
    sf::Texture texture;
    sf::Sprite sprite;

    ///    Load image frome png file   ///
    if(!texture.loadFromFile("res/texture.png"))
        return 0;
    sprite.setTexture(texture);

    ///    Texts and Fonts             ///
    sf::Font font;
    sf::Text text;
    sf::String textS;

    ///    Load font from ttf file     ///
    if(!font.loadFromFile("res/sansation.ttf"))
        return 0;
    text.setFont(font);
    text.setPosition(30,200);
    text.setFillColor(sf::Color::Red);
    text.setOutlineColor(sf::Color::Green);
    text.setOutlineThickness(3);
    ///    Variable to manage activity ///
    short int i,j;
    unsigned short int data[3][3] = {PNONE};
    unsigned short int player = PlayerO;
    unsigned short int count = 0;
    bool isGameFinished = false;

    ///   Window and EventHandler     ///
    sf::RenderWindow app;
    sf::Event e;
    sf::Vector2i MousePosition;

    ///       Create window here       ///
    app.create(sf::VideoMode(450,450),"Tic Tac Toe");

    ///        window's main loop      ///
    while(app.isOpen())
    {
        ///   Handle user events  ///
        while(app.pollEvent(e))
        {
            /// If user clicked close button ///
            if(e.type == sf::Event::Closed)
                app.close();
            /// If user pressed any key      ///
            else if(e.type == sf::Event::KeyPressed)
            {
                /// Key press event only run if game is finished(either won by anyone or it's a draw)
                if(isGameFinished)
                {
                    /// If key is pressed (after game finished) it will reset game
                    isGameFinished = false;
                    for(i = 0; i < 3; i++)
                        for(j = 0; j < 3; j++)
                        {
                            data[i][j] = PNONE;
                        }
                    text.setString("");
                    count = 0;
                }
            }
            /// If player clicked (mouse) on board ///
            else if(e.type == sf::Event::MouseButtonPressed)
            {
                /// If click button is left click and game is not finished ///
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isGameFinished)
                {
                    /// Get mouse position relative to app      ///
                    MousePosition = sf::Mouse::getPosition(app);
                    i = MousePosition.y/150;
                    j = MousePosition.x/150;

                    if(i > 2 || j > 2)
                        continue;

                    /// check if it is already not used, then use ///
                    if(data[i][j] == PNONE)
                    {
                        data[i][j] = player;
                        player = (player == PlayerO)?PlayerX:PlayerO;
                        count++;
                    }
                }
            }
        }//End of event

        ///   Clear previous screen      ///
        app.clear();

        ///   Main drawing starts here   ///
        ///   Draw sprites here          ///
        for(i = 0; i < 3; i++)
            for(j = 0; j < 3; j++)
            {
                sprite.setTextureRect(sf::IntRect(PixelSize*data[i][j],0,PixelSize,PixelSize));
                sprite.setPosition(float(PixelSize*j),float(PixelSize*i));
                app.draw(sprite);
            }

        ///   If count >= 5 (2 + 3) possibility of winning game ///
        if(!isGameFinished && count >= 5)
        {
            int winner = getWinner(data);
            /// If winner is none then any player has won the game ///
            if(winner != PNONE)
            {
                textS.clear();
                textS = (winner == PlayerO)?("PlayerO"):("PlayerX");
                textS += " Has Won The Game\nPress Any Key To Play Again";
                text.setString(textS);
                isGameFinished = true;
            }
            /// If count = 9 and winner is none then it's a draw   ///
            else if(count == 9)
            {
                textS.clear();
                textS = "\t\t\tGame Is Draw\nPress Any Key To Play Again";
                text.setString(textS);
                isGameFinished = true;
            }
        }
        ///     Draw text here      ///
        app.draw(text);
        ///     Display all drawing ///
        app.display();
    }//End of loop

    ///  return exit success   ///
    return 0;
}
