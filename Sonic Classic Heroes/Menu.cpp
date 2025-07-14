#include "Menu.h"


// Constructor
Menu::Menu()
{

	leaderBoardText = new Text;
	leaderBoardText->setFont(menuFont);
	leaderBoardText->setCharacterSize(33);
	leaderBoardText->setString("Leader Board");
	leaderBoardText->setFillColor(Color::Yellow);
	leaderBoardText->setScale(2.5, 2.5);
	leaderBoardText->setPosition(1200 / 2 - 200, 40);


	nameText = new Text[max_records];
	scoreText = new Text[max_records];
	pausMenu = new Text[3];
	name = new std::string;

	
	selectedCol = Color::White;
	nonSelectedCol = Color::Yellow;
	menuMusic.openFromFile("Data/mainMenu.ogg");
	menuMusic.setVolume(30);
	menuMusic.setLoop(true);

	gameOver.openFromFile("Data/gameOver_m.ogg");
	gameOver.setVolume(30);
	//menuMusic.setLoop(true);

	win.openFromFile("Data/winMusic.ogg");
	win.setVolume(30);
	//menuMusic.setLoop(true);


	
	buttonMusic.openFromFile("Data/MenuButton.wav");

	optionText[0].setString("Play/Pause Music");
	optionText[1].setString("Set Volume (+/-)");
	optionText[2].setString("Back to Menu");

	nameWindow.setString("Enter Name : ");
	
	menuFont.loadFromFile("Data/textFont.otf");

	menuText[0].setString("START");
	menuText[1].setString("OPTIONS");
	menuText[2].setString("CREDITS");
	menuText[3].setString("LOAD");
	menuText[4].setString("EXIT");


	pausMenu[0].setString("Resume");
	pausMenu[1].setString("Save Game");
	pausMenu[2].setString("Return to menu");

	
	
	setFont(menuText, TotalMenu);


	menuTex.loadFromFile("Data/Menu.png");
	menuSprite.setTexture(menuTex);

	fileAddress = "Data/records.txt";

	menu_bg_tex = new Texture;
	menu_bg_tex->loadFromFile("Data/menu_bg.png");

	menu_bg_sprite = new Sprite;
	menu_bg_sprite->setTexture(*menu_bg_tex);


	lvlImg = new Sprite;
	lvlImg_tex = new Texture;
	lvlImg_tex->loadFromFile("Data/lvlImg.png");

	lvlImg->setTexture(*lvlImg_tex);

	congrats = new Sprite;
	congrats_tex = new Texture;
	congrats_tex->loadFromFile("Data/congrats.png");
	congrats->setTexture(*congrats_tex);

	game_over = new Sprite;
	game_over_tex = new Texture;
	game_over_tex->loadFromFile("Data/gameOver.png");
	game_over->setTexture(*game_over_tex);
}


// Destructor
Menu::~Menu()
{
	delete game_over;
	delete game_over_tex;
	delete congrats;
	delete congrats_tex;
	delete lvlImg;
	delete lvlImg_tex;
	delete leaderBoardText;
	delete[] nameText;
	delete[] scoreText;
	delete[] pausMenu;
	delete name;

	delete menu_bg_tex;
	delete menu_bg_sprite;
}



void Menu::runMusic(bool& startOfgame)
{
	if (startOfgame) {
		//menuMusic.stop();
		menuMusic.play();

	}
}

void Menu::run(RenderWindow& window, bool& startOfgame, bool& loadSveGame)
{
	View v = window.getDefaultView();
	selected = 0;
	runMusic(startOfgame);
	startOfgame = false;
	while (window.isOpen()) {

		// Chekcing selection
		// Persuiing with that selection

		Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == Event::KeyPressed) {
				if (ev.key.code == Keyboard::Up) {
					buttonMusic.play();
					selected = (selected - 1) % TotalMenu;
				}
				else if (ev.key.code == Keyboard::Down) {
					buttonMusic.play();

					selected = (selected + 1) % TotalMenu;
				}


				// Handling the event
				if (ev.key.code == Keyboard::Enter) {
					buttonMusic.play();

					switch (selected)
					{
						case 0: enterNameScreen(window);
								menuMusic.stop();
								return; // returning to the main game loop
								break; 
						case 1: options(window);
								break;
						case 2: leaderBoard(window);
								break;
						case 3: loadSveGame = true;
							menuMusic.stop();
							return;
							break;

						case 4: window.close();
								break;
					
					}
				}
			}
		}

		window.clear();
		window.draw(*menu_bg_sprite);
		setFont(menuText, TotalMenu);
		

		//window.draw(menuSprite);
		for (int i = 0; i < TotalMenu; i++) {
			window.draw(menuText[i]);
		}
		window.setView(v);
		window.display();
	}
}

// Displyaing the inbetween level display
void Menu::lvlImageDisplay(RenderWindow& window)
{
	clock.restart();
	while (clock.getElapsedTime().asSeconds() < maxTime) {
		window.clear();
		window.draw(*lvlImg);
		window.display();
	}
	
}

// displaying the congratulation window
void Menu::congratsDisplay(RenderWindow& window)
{
	win.play();
	clock.restart();
	while (clock.getElapsedTime().asSeconds() < maxTime) {
		window.clear();
		window.draw(*congrats);
		window.display();
	}
	win.stop();
}


// game over window
void Menu::gameOverDisplay(RenderWindow& window)
{
	gameOver.play();
	clock.restart();
	while (clock.getElapsedTime().asSeconds() < maxTime) {
		window.clear();
		window.draw(*game_over);
		window.display();
	}
	gameOver.stop();

}

// setting font of the the text
void Menu::setFont(Text* obj, int size)
{
	int spacing = 0;
	for (int i = 0; i < size; i++) {
		obj[i].setFont(menuFont);
		obj[i].setFillColor((i == selected) ? selectedCol : nonSelectedCol);
		obj[i].setScale(2.5, 2.5);
		obj[i].setPosition(1200 / 2 - 130, 900 / 4 + spacing);
		spacing += 100;
	}
}

// it is beign used when showing data to the leaderboard
void Menu::setFont(string* Name, int* Scoring)
{
	//int spacing = 0;
	for (int i = 0; i < max_records; i++) {
		nameText[i].setFont(menuFont);
		nameText[i].setString(to_string(i + 1) + '.' + Name[i]);
		nameText[i].setCharacterSize(24);
		nameText[i].setFillColor(Color:: White);
		nameText[i].setScale(2.5, 2.5);
		nameText[i].setPosition(1200 / 2 - 350 , 150 + i*60);
		//spacing += 100;

		scoreText[i].setFont(menuFont);
		scoreText[i].setString(to_string(Scoring[i]));
		scoreText[i].setCharacterSize(24);
		scoreText[i].setFillColor(Color::White);
		scoreText[i].setScale(2.5, 2.5);
		scoreText[i].setPosition(1200 / 2 + 200, 170 + i * 60);
	}
}

// options window
void Menu::options(RenderWindow& window)
{
	selected = 0;
	while (window.isOpen()) {

		Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == Event::KeyPressed) {
				if (ev.key.code == Keyboard::Up) {
					buttonMusic.play();

					selected = (selected - 1) % Totaloption;
				}
				else if (ev.key.code == Keyboard::Down) {
					buttonMusic.play();

					selected = (selected + 1) % Totaloption;
				}


				// Handling the event
				if (selected == 0) {
					if (ev.key.code == Keyboard::Enter) {
						buttonMusic.play();

						if (menuMusic.getStatus() == SoundSource::Playing) {
							menuMusic.pause();
						}
						else
							menuMusic.play();
					}
				}
				else if (selected == 1) {
					float vol = menuMusic.getVolume();
					if (ev.key.code == Keyboard::Add || ev.key.code == sf::Keyboard::Equal) {
						buttonMusic.play();

						if (vol < 100) {
							vol++;
							menuMusic.setVolume(vol);
						}
					}

					else if (ev.key.code == Keyboard::Subtract || ev.key.code == sf::Keyboard::Hyphen) {
						buttonMusic.play();

						if (vol > 0) {
							vol--;
							menuMusic.setVolume(vol);
						}
					}

				}
				else if (selected == 2) {
					if (ev.key.code == Keyboard::Enter) {
						buttonMusic.play();

						return;
					}
						//return;
				}
			
			}
		}

		window.clear();
		setFont(optionText, Totaloption);


		//window.draw(menuSprite);
		for (int i = 0; i < Totaloption; i++) {
			window.draw(optionText[i]);
		}
		window.display();
	}
}


// pause menu window
void Menu::PauseMenu(RenderWindow& window, bool& startOfGame, bool& saveGame)
{

	View defaultView = window.getDefaultView();

	selected = 0;
	while (window.isOpen()) {

		Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == Event::KeyPressed) {
				if (ev.key.code == Keyboard::Up) {
					buttonMusic.play();


					selected = (selected - 1) % TotalPause;
				}
				else if (ev.key.code == Keyboard::Down) {
					buttonMusic.play();

					selected = (selected + 1) % TotalPause;
				}


				if (ev.key.code == Keyboard::Enter) {
					buttonMusic.play();

					switch (selected) {
					case 0: 
						return;
					case 1:  saveGame = true;
						// do save…
						return;
					case 2:  // Return to Menu
						//cout << "in the pause menu, setted the start of game to true" << endl;
						startOfGame = true;
						return;
					}


				}

			}
		}

		window.clear();
		window.setView(defaultView);
		setFont(pausMenu, TotalPause);


		//window.draw(menuSprite);
		for (int i = 0; i < TotalPause; i++) {
			window.draw(pausMenu[i]);
		}
		window.display();
	}
}

void Menu::setScore(int* score)
{
	this->score = score;
}

void Menu::updateBoard()
{

	/*
		I am doing the following steps to add records to the file
		1. Open the file and retreive all the data into two arrys. Names go into name array and points go into points array.
		2. Then sort those array in descending order.
		3. After sorting , Compare the lowest point value with the current points.
		4. If greater then swap them.
		5. Then resort the arrays in descending order.
		6. Now open the file in write mode(clearing all the previous data), fill the file with the data from the two arrays
	*/


	// Temporary arrays
	string* Names = new string[10];
	int* scorings = new int[10];

	fstream myfile;
	myfile.open(fileAddress, ios::in);
	if (!myfile.is_open())
		cout << "Error openning the record file. " << endl;

	while (myfile.is_open()) {

		for (int i = 0; i < max_records; i++) {
			myfile >> Names[i] >> scorings[i];
		}

		myfile.close();
	}

	//Sorting the data in decsendigng order
	for (int i = 0; i < 9; i++) {

		for (int j = i + 1; j < 10; j++) {

			if (scorings[i] < scorings[j]) {
				// swap(Point[i], Point[j]);
					// swap(Name[i], Name[j]);

				int temp = scorings[i];
				scorings[i] = scorings[j];
				scorings[j] = temp;

				string tempo = Names[i];
				Names[i] = Names[j];
				Names[j] = tempo;
			}

		}
	}


	//Comparing the loweset value data with the points 
	if (*score > scorings[max_records - 1]) {
		scorings[max_records - 1] = *score;
		Names[max_records - 1] = *name;
	}

	//Resorting
	for (int i = 0; i < max_records - 1; i++) {

		for (int j = i + 1; j < max_records; j++) {

			if (scorings[i] < scorings[j]) {
				// swap(Point[i], Point[j]);
					// swap(Name[i], Name[j]);

				int temp = scorings[i];
				scorings[i] = scorings[j];
				scorings[j] = temp;

				string tempo = Names[i];
				Names[i] = Names[j];
				Names[j] = tempo;
			}

		}
	}


	//Writing data to the file
	myfile.open(fileAddress, ios::out);
	while (myfile.is_open()) {

		for (int i = 0; i < max_records; i++) {

			myfile << Names[i] << " " << scorings[i] << '\n';
		}
		myfile.close();
	}


}

void Menu::enterNameScreen(RenderWindow& window)
{

	bool firstChar = true;
	setFont(&nameWindow, 1);
	
	while (window.isOpen()) {
		Event ev;

		while (window.pollEvent(ev)) {
			if (ev.type == Event::TextEntered) {

				if (ev.text.unicode == '\r') {
					if (firstChar)
					{
						// swallow it and keep going
						firstChar = false;
						continue;
					}
					else
					{
						// this is the “real” Enter
						return;
					}
				}
				
				firstChar = false;
			
				if (ev.text.unicode < 128) {
					
					*name += (char)ev.text.unicode;
				}
			}


			nameWindow.setString("Enter Name : " + *name);

		}
		
		window.clear();
		window.draw(nameWindow);
		window.display();
	}
}

void Menu::leaderBoard(RenderWindow& window)
{
	
	// Temporary arrays to hold the data;
	int* Scoring = new int[max_records];
	string* Name = new string[max_records];

	fstream myfile;
	myfile.open(fileAddress, ios::in);
	while (myfile.is_open()) {
		for (int i = 0; i < max_records; i++) {
			myfile >> Name[i] >> Scoring[i];
		}

		myfile.close();
	}


	

	setFont(Name, Scoring);


	delete[]Scoring;
	delete[]Name;
	Scoring = nullptr;
	Name = nullptr;
	

	while (window.isOpen()) {

		Event ev;
		while (window.pollEvent(ev)) {

			if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Enter) {
				return;
			}

			if (ev.type == Event::Closed)
				window.close();

		}


		window.clear();
		for (int i = 0; i < max_records; i++) {
			//window.draw(leaderBoardText[i]);
			window.draw(nameText[i]);
			window.draw(scoreText[i]);
		}
		window.draw(*leaderBoardText);
		window.display();
	}


}



