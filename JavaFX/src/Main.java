//150119042 Ahmet Emre Saðcan - 150118047 Mehmet Safa KATIRCIOÐLU
//This program makes a game which builds a path for the ball like a puzzle.
import javafx.application.Application;	//Some imports we used.
import javafx.stage.Stage;
import javafx.util.Duration;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.paint.Color;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;
import javafx.scene.shape.Line;
import javafx.scene.shape.Arc;
import javafx.animation.PathTransition;
import javafx.scene.text.Text;
import javafx.scene.control.Button;

public class Main extends Application {
	
	//These are all some static variables so they can be used in following parts of the program as shared variables.
	public static boolean isFinished; //Checks whether that level is finished or not.
	public static int move_counter; //Counts moves.
	public static int currentLevel = 1; //Holds the current level's number
	
	//These are our main parts in game gridpane contains tiles' images. Tiles ArrayList contains tiles. mainPane contains everything in game.
    public static GridPane gridpane = new GridPane(); 
    public static ArrayList<Tile> tiles = new ArrayList<>();
	public static BorderPane mainPane = new BorderPane();
    public static Text moveCount = new Text("Number of Moves: " + move_counter); 
	public static Scene scene = new Scene(mainPane, 258, 320);
	//Buttons for the levels.
	public static Button level1 = new Button(); 
	public static Button level2 = new Button();
	public static Button level3 = new Button();
	public static Button level4 = new Button();
	public static Button level5 = new Button();
	public static BorderPane buttons = new BorderPane(); //Pane which contains buttons.
    
	
	
    public void start(Stage primaryStage) throws Exception {
    	primaryStage.getIcons().add(new Image("icon.png")); //Sets the icon of the application.
    	
    	level5.setGraphic(new ImageView(new Image("level5.png"))); //Sets the level 5's X,Y coordinates, image and max width,height values.
    	level5.setMaxWidth(32);
    	level5.setMaxHeight(16);
    	level5.setTranslateX(170);
    	level5.setTranslateY(16);
    	
    	level4.setGraphic(new ImageView(new Image("level4.png"))); //Sets the level 4's X,Y coordinates, image and max width,height values.
    	level4.setMaxWidth(32);
    	level4.setMaxHeight(16);
    	level4.setTranslateX(132);
    	level4.setTranslateY(16);
    	
    	level3.setGraphic(new ImageView(new Image("level3.png"))); //Sets the level 3's X,Y coordinates, image and max width,height values.
    	level3.setMaxWidth(32);
    	level3.setMaxHeight(16);
    	level3.setTranslateX(94);
    	level3.setTranslateY(16);
    	
    	level2.setGraphic(new ImageView(new Image("level2.png"))); //Sets the level 2's X,Y coordinates, image and max width,height values.
    	level2.setMaxWidth(32);
    	level2.setMaxHeight(16);
    	level2.setTranslateX(56);
    	level2.setTranslateY(16);
    	
    	level1.setGraphic(new ImageView(new Image("level1.png"))); //Sets the level 1's X,Y coordinates, image and max width,height values.
    	level1.setMaxWidth(32);
    	level1.setMaxHeight(16);
    	level1.setTranslateX(18);
    	level1.setTranslateY(16);
    	buttons.getChildren().add(level1); //Adds it as the first button because it should be accessible at the start of the program.
    	
    	mainPane.setStyle("-fx-background-color: darkblue"); //Sets the background color of mainpane.
    	BorderPane menu = new BorderPane(new ImageView(new Image("menu.png"))); //Creates a menu pane.
    	
    	Button quit = new Button(); //Creates and sets the button's X,Y coordinates and image. Then adds it to pane.
    	quit.setGraphic(new ImageView(new Image("exitButton.png"))); 
    	quit.setTranslateX(129);
    	quit.setTranslateY(150);
    	menu.getChildren().add(quit);
    	
    	Button start  = new Button(); //Creates and sets the button's X,Y coordinates and image. Then adds it to pane.
    	start.setGraphic(new ImageView(new Image("startButton.png"))); 
    	start.setTranslateX(129);
    	start.setTranslateY(110);
    	menu.getChildren().add(start);
    	
    	Scene entrance = new Scene(menu, 258, 320);
    	primaryStage.setResizable(false);
    	primaryStage.setScene(entrance);
    	primaryStage.show(); //Shows the for the first time after setting the size of scene.
    	

    	Scanner sc = new Scanner(new File("level1.txt")); //This scans level1.txt for only the first time.
    	
		primaryStage.setTitle("PATH");
		gridpane.setHgap(1);  //Sets some properties of the gridpane.
		gridpane.setVgap(1); 
		gridpane.setTranslateX(0);
		gridpane.setTranslateY(32);
    	
		start.setOnAction(e -> createGrid(sc, primaryStage)); //Loads the first level when pressed.
    	
    	quit.setOnAction(e -> primaryStage.close()); //Closes the game when pressed.
        
        
    	level1.setOnAction(e ->{ //Also loads the first level when pressed and updates the values properly.
    		isFinished = false;
    		currentLevel = 1;
			try {
				 //Uses another scanner which is created everytime the button is pressed and then creates the level from that scanner in method.
				Scanner sc6 = new Scanner(new File("level1.txt"));
		        createGrid(sc6, primaryStage);
			} catch (FileNotFoundException e1) {}
    	});
    	level2.setOnAction(e ->{ //Loads the second level when pressed and updates the values properly.
    		isFinished = false;
    		currentLevel = 2;
    		try {
    			//Uses the scanner which is created everytime the button is pressed and then creates the level from that scanner in method.
				Scanner sc2 = new Scanner(new File("level2.txt")); 
	        	createGrid(sc2, primaryStage);
			} catch (FileNotFoundException e1) {}
    	});
    	level3.setOnAction(e ->{ //Loads the third level when pressed and updates the values properly.
    		isFinished = false;
    		currentLevel = 3;
    		try {
    			//Uses the scanner which is created everytime the button is pressed and then creates the level from that scanner in method.
				Scanner sc3 = new Scanner(new File("level3.txt")); 
	        	createGrid(sc3, primaryStage);
			} catch (FileNotFoundException e1) {}
    	});
    	level4.setOnAction(e ->{ //Loads the fourth level when pressed and updates the values properly.
    		isFinished = false;
    		currentLevel = 4;
    		try {
    			//Uses the scanner which is created everytime the button is pressed and then creates the level from that scanner in method.
				Scanner sc4 = new Scanner(new File("level4.txt"));
	        	createGrid(sc4, primaryStage);
			} catch (FileNotFoundException e1) {}
    	});
    	level5.setOnAction(e ->{ //Loads the fifth level when pressed and updates the values properly.
    		isFinished = false;
    		currentLevel = 5;
    		try {
    			//Uses the scanner which is created everytime the button is pressed and then creates the level from that scanner in method.
				Scanner sc5 = new Scanner(new File("level5.txt"));
	        	createGrid(sc5, primaryStage);
			} catch (FileNotFoundException e1) {}
    	});
    	
    	//Finds the index of the tile by taking the coordinates.
        gridpane.setOnMousePressed(e->{
       		int x = (int) e.getX() / 64;
       		int y = (int) e.getY() / 64;
       		int index = y * 4 + x;	
       		if(isFinished == false) {
       			if(index < 16) 
           			move(index);
       		}
       	});
        
    }
    //Grid is created in this part.
    public static void createGrid(Scanner sc, Stage primaryStage) {
    	move_counter = 0; //Sets it as zero every time a level is created.
    	moveCount.setText("Number of Moves: " + move_counter);
    	//Clears ArrayLists every time and adds the essential ones.
    	tiles.clear(); 
    	gridpane.getChildren().clear();
    	mainPane.getChildren().clear();
        mainPane.getChildren().add(moveCount);
    	mainPane.getChildren().add(buttons);
        moveCount.setX(5);
        moveCount.setY(312);
        moveCount.setFill(Color.AQUA);
    	while(sc.hasNext()) { //Scans the level file and adds them in an order to the tiles array.
        	String[] insets = sc.next().split(",");
        	int id = Integer.parseInt(insets[0]);
        	Tile tile = new Tile(id, insets[1], insets[2]);
        	tiles.add(tile);
        }
        int k = 0, l = 0;
        for(int i = 0; i < tiles.size(); i++) {
       		for(int j = 1; j <= 16; j++) {
       			if(j == tiles.get(i).getID()) {			
       				if(k > 3) {
       					k = 0;
       					l++;
       				}
       				if(l > 3)
       					break;
        			gridpane.add(tiles.get(i).getImage(),k,l); //Then checks for their IDs and puts that tile in gridpane in order. 
        			k++;
        		}
       		}
       	}
        for(int i = 0 ; i < tiles.size() ;i++) { //Places the ball to the place where the starter tile's center point is.
        	if(tiles.get(i).getFeature().equals("Starter")) {
        		ImageView ball = new ImageView(new Image("Ball.png"));
        		ball.setX(tiles.get(i).getImage().getX() + 16);
        		ball.setY(tiles.get(i).getImage().getY() + 48);
        		//And adds them in order to the mainPane.
        		mainPane.getChildren().add(gridpane); 
        		mainPane.getChildren().add(ball);
        	}
        }
        primaryStage.setResizable(false);
        primaryStage.setScene(scene);
        primaryStage.show(); 
    }
    
    //Movements, animations and texts in scene are handled here.
    public static void move(int index) {
    	tiles.get(index).getImage().setOnMouseDragged(e ->{ //This method works when mouse is dragged.
    		if(tiles.get(index).isStatic() == false) { //Checks that tile's status in terms of movability.
    			/** RIGHT **/
    			//Check if the player wants to move right and if that is possible shifts the tile.
    			if(e.getX() - tiles.get(index).getImage().getX() > 64 && tiles.get(index).movableToRight(gridpane, tiles)) { 
    				gridpane.setColumnIndex(tiles.get(index + 1).getImage(),gridpane.getColumnIndex(tiles.get(index + 1).getImage()) -1);
    				gridpane.setColumnIndex(tiles.get(index).getImage(),gridpane.getColumnIndex(tiles.get(index).getImage()) +1);
    				Tile temp  = tiles.get(index + 1);
    				tiles.set(index + 1, tiles.get(index));
    				tiles.set(index, temp);
    				move_counter++;
    			} 
    			/** LEFT **/
    			//Check if the player wants to move left and if that is possible shifts the tile.
    			else if(e.getX() - tiles.get(index).getImage().getX() < 0  && tiles.get(index).movableToLeft(gridpane, tiles)) {    				
    				gridpane.setColumnIndex(tiles.get(index - 1).getImage(),gridpane.getColumnIndex(tiles.get(index - 1).getImage()) +1);
    				gridpane.setColumnIndex(tiles.get(index).getImage(),gridpane.getColumnIndex(tiles.get(index).getImage()) -1);
    				Tile temp  = tiles.get(index - 1);
    				tiles.set(index - 1, tiles.get(index));
    				tiles.set(index, temp);
    				move_counter++;
    			}
    			/** DOWN **/
    			//Check if the player wants to move down and if that is possible shifts the tile.
    			else if(e.getY() - tiles.get(index).getImage().getY() > 64  && tiles.get(index).movableToDown(gridpane, tiles)) {
    				gridpane.setRowIndex(tiles.get(index).getImage(),gridpane.getRowIndex(tiles.get(index).getImage()) +1);
    				gridpane.setRowIndex(tiles.get(index + 4).getImage(),gridpane.getRowIndex(tiles.get(index + 4).getImage()) -1);
    				Tile temp  = tiles.get(index + 4);
    				tiles.set(index + 4, tiles.get(index));
    				tiles.set(index, temp);
    				move_counter++;
    			}
    			/** UP **/
    			//Check if the player wants to move up and if that is possible shifts the tile.
    			else if(e.getY() - tiles.get(index).getImage().getY() < 0  && tiles.get(index).movableToUp(gridpane, tiles)) {    				
    				gridpane.setRowIndex(tiles.get(index).getImage(),gridpane.getRowIndex(tiles.get(index).getImage()) -1);
    				gridpane.setRowIndex(tiles.get(index - 4).getImage(),gridpane.getRowIndex(tiles.get(index - 4).getImage()) +1);
    				Tile temp  = tiles.get(index - 4);
    				tiles.set(index - 4, tiles.get(index));
    				tiles.set(index, temp);
    				move_counter++;
    			}
				moveCount.setText("Number of Moves: " + move_counter); //Updates the text everytime a new movement is done.
    		}
    		if(checkGrid(tiles) && isFinished == false) { // If it is finished and grid is complete updates the isFinished value.
    			isFinished = true;
    			if(tiles.get(15).getFeature().equals("End")) { //If it is first,second or third level ball plays that level's animation because actually they have the same animation.
    				
    				//Path is created in here using lines and arcs and ball follows these shapes in animation.
    				Line lineVDown = new Line(32, 64, 32, 230);
    				Arc arc01 = new Arc(64, 230, 32, 32, 180, 90);
    				Line lineH = new Line(64, 262, 230, 262);
    				PathTransition pathVDown = new PathTransition(Duration.seconds(1), lineVDown, mainPane.getChildren().get(3));
    				
    				PathTransition pathArc01 = new PathTransition(Duration.seconds(0.5), arc01, mainPane.getChildren().get(3));
    				pathArc01.setDelay(Duration.millis(900));
    				PathTransition pathH = new PathTransition(Duration.seconds(1), lineH, mainPane.getChildren().get(3));
    				pathH.setDelay(Duration.millis(1400));
    				pathVDown.play();
    				pathArc01.play();
    				pathH.play();
    			
    				if(currentLevel == 1) { //Also if first level is completed for the first time, program adds the level2 button to the screen so that player can go to that level.
    					try {
    					buttons.getChildren().add(level2); 
    					}catch (Exception ex) { }
    					if(move_counter == 1) { //This is an additional feature. If user has done the best in the level 1 it prints a text to the scene.
    						Text perfectCount = new Text("PERFECT (" + move_counter +" moves)");
    						perfectCount.setX(150);
    						perfectCount.setY(312);
    						mainPane.getChildren().add(perfectCount);
    						perfectCount.setFill(Color.WHITE);
    					}
    				}   	
    				else if(currentLevel == 2) { //If second level is completed for the first time, program adds the level3 button to the screen so that player can go to that level.v
    					try {
        					buttons.getChildren().add(level3); 
        					}catch (Exception ex) { }
    					if(move_counter == 4) { //If user has done the best in the level 2 it prints a text to the scene.
    						Text perfectCount = new Text("PERFECT (" + move_counter +" moves)");
    						perfectCount.setX(150);
    						perfectCount.setY(312);
    						mainPane.getChildren().add(perfectCount);
    						perfectCount.setFill(Color.WHITE);
    					}
    				}
    				else if(currentLevel == 3) { //If third level is completed for the first time, program adds the level4 button to the screen so that player can go to that level.
    					try {
        					buttons.getChildren().add(level4); 
        					}catch (Exception ex) { }
    					if(move_counter == 8) { //If user has done the best in the level 3 it prints a text to the scene.
    						Text perfectCount = new Text("PERFECT (" + move_counter +" moves)");
    						perfectCount.setX(150);
    						perfectCount.setY(312);
    						mainPane.getChildren().add(perfectCount);
    						perfectCount.setFill(Color.WHITE);
    					}
    				}
    			}
    			else if(tiles.get(7).getFeature().equals("End")) { //If it is fourth of fifth level ball plays that level's animation because actually they have the same animation.
    				//Path is created in here using lines and arcs and ball follows these shapes in animation.
    				Line lineVDown = new Line(32, 64, 32, 164);
    				Arc arc01 = new Arc(64, 164, 32, 32, 180, 90);
    				Line lineH = new Line(64, 196, 198, 196);
    				Arc arc00 = new Arc(198, 164, 32, 32, 270, 90);
    				Line lineVUp = new Line(230, 166, 230, 132);
    				PathTransition pathVDown = new PathTransition(Duration.seconds(0.60), lineVDown, mainPane.getChildren().get(3));
    				
    				PathTransition pathArc01 = new PathTransition(Duration.seconds(0.50), arc01, mainPane.getChildren().get(3));
    				pathArc01.setDelay(Duration.millis(500));
    				PathTransition pathH = new PathTransition(Duration.seconds(0.80), lineH, mainPane.getChildren().get(3));
    				pathH.setDelay(Duration.millis(1000));
    				PathTransition pathArc00 = new PathTransition(Duration.seconds(0.5), arc00, mainPane.getChildren().get(3));
    				pathArc00.setDelay(Duration.millis(1800));
    				PathTransition pathVUp = new PathTransition(Duration.seconds(1), lineVUp, mainPane.getChildren().get(3));
    				pathVUp.setDelay(Duration.millis(2300));
    				pathVDown.play();
    				pathArc01.play();
    				pathH.play();
    				pathArc00.play();
    				pathVUp.play();
    				if(currentLevel == 4) { //If fourth level is completed for the first time, program adds the level5 button to the screen so that player can go to that level.
    					try {
        					buttons.getChildren().add(level5); 
        					}catch (Exception ex) { }
    					if(move_counter == 6) { //If user has done the best in the level 4 it prints a text to the scene.
    						Text perfectCount = new Text("PERFECT (" + move_counter +" moves)");
    						perfectCount.setX(150);
    						perfectCount.setY(312);
    						mainPane.getChildren().add(perfectCount);
    						perfectCount.setFill(Color.WHITE);
    					}
    				}
    				if(currentLevel == 5) {
    					if(move_counter == 8) { //If user has done the best in the level 5 it prints a text to the scene.
    						Text perfectCount = new Text("PERFECT (" + move_counter +" moves)");
    						perfectCount.setX(150);
    						perfectCount.setY(312);
    						mainPane.getChildren().add(perfectCount);
    						perfectCount.setFill(Color.WHITE);
    					}
    				}
    			}
    		}
    	});
    }
    //Checks whether there is a proper path for ball.
    public static boolean checkGrid(ArrayList<Tile> tiles) {
    	for(int i = 0; i < tiles.size(); i++) {
    		if(tiles.get(i).getFeature().equals("Starter")) { //Checks the grid starting from starter tile and checks the proper side of the tile according to that object's property.
    			if(tiles.get(i).getProperty().equals("Vertical")) {
    				i += 4;
    			}
    			else if(tiles.get(i).getProperty().equals("Horizontal")) {
    				i += 1;
    			}
    			while(!(tiles.get(i).getFeature().equals("End"))) { //Checks each tiles until it reaches to the end.
                    if(tiles.get(i).getProperty().equals("Vertical") && i < 12 && i > 3) {
                        i += 4;
                    }
                    else if(tiles.get(i).getProperty().equals("Horizontal") && i!= 0 && i != 3 && i != 4 && i != 7 && i != 8 && i != 11 && i != 12 && i != 15) {
                        i += 1;
                    }
                    else if(tiles.get(i).getProperty().equals("00") && !tiles.get(i - 4).getProperty().contentEquals("Horizontal") && i > 4 && i != 8 && i != 12) {
                        i -= 4;
                    }
                    else if(tiles.get(i).getProperty().equals("01") && !tiles.get(i + 1).getProperty().contentEquals("Vertical") && i > 3 && i != 7 && i!= 11 && i!= 15) {
                        i += 1;
                    }
                    else if(tiles.get(i).getProperty().equals("10") && !tiles.get(i + 4).getProperty().contentEquals("Horizontal") &&  i < 12 && i != 0 && i != 4 && i != 8) {
                        i += 4;
                    }
                    else if(tiles.get(i).getProperty().equals("11") && !tiles.get(i - 4).getProperty().contentEquals("Vertical") && i < 12 && i != 3 && i != 7 && i!= 11 ) {
                        i += 1;
                    }
                    else {
                        return false;
                    }
                }
    			return true;
    		}
    	}
		return false;
    }
    //Launches the program.
    public static void main(String[] args) {
		launch(args);
	}
}
	//A class for making it easy to work with tiles.
	class Tile { 
	
		private int ID; //ID of tile.
		private boolean isStatic; //Status of tile.
		private String feature; //Feature of tile.
		private String property; //Property of tile.
		private ImageView image = null; ////Image of tile.
		
		Tile (int id, String isStatic, String property) { //Constructor for making a tile object.
			ID = id;
			feature = isStatic;
			if(isStatic.equals("Starter") || isStatic.equals("PipeStatic") || isStatic.equals("End")) //Arranges the isStatic value of object according to the isStatic string.
				this.isStatic = true;
			else
				this.isStatic = false;
			this.property = property;
			
			
			switch(property) { //Creates an ImageView by considering the property value.
			
			case "Vertical": //If it is vertical it looks for the isStatic string and decides the image according to it.
				if(isStatic.equals("End")) 
					image = new ImageView(new Image("EndV.png"));
				else if(isStatic.equals("Starter")) 
					image = new ImageView(new Image("StarterV.png"));
				else if(isStatic.equals("PipeStatic"))
					image = new ImageView(new Image("StaticPipeV.png"));
				else
					image = new ImageView(new Image("PipeV.png"));
				break;
			case "Horizontal": //If it is horizontal it looks for the isStatic string and decides the image according to it.
				if(isStatic.equals("End")) 
					image = new ImageView(new Image("EndHR.png"));
				else if(isStatic.equals("Starter")) 
					image = new ImageView(new Image("StarterHR.png"));
				else if(isStatic.equals("PipeStatic"))
					image = new ImageView(new Image("StaticPipeH.png"));
				else 
					image = new ImageView(new Image("PipeH.png"));
				break;
			case "01": //If it is 01 it looks for the isStatic string and decides the image according to it.
				if(isStatic.equals("PipeStatic"))
					image = new ImageView(new Image("Static01.png"));
				else
					image = new ImageView(new Image("01.png"));
				break;
			case "00": //If it is 00 it looks for the isStatic string and decides the image according to it.
				if(isStatic.equals("PipeStatic"))
					image = new ImageView(new Image("Static00.png"));
				else
					image = new ImageView(new Image("00.png"));
				break;
			case "11": //If it is 11 it looks for the isStatic string and decides the image according to it.
				if(isStatic.equals("PipeStatic"))
					image = new ImageView(new Image("Static11.png"));
				else
					image = new ImageView(new Image("11.png"));
			case "10": //If it is 10 it looks for the isStatic string and decides the image according to it.
				if(isStatic.equals("PipeStatic"))
					image = new ImageView(new Image("Static10.png"));
				else
					image = new ImageView(new Image("10.png"));
			case "Free": //If it is free creates an image for it.
				image = new ImageView(new Image("Free.png"));
				break; 
			case "none": //If it is none creates an image for it.
				image = new ImageView(new Image("Empty.png"));
				break;
			}
					
		}

		public String getProperty() { //Gets the property.
			return property;
		}

		public void setProperty(String property) { //Sets the property.
			this.property = property;
		}

		public int getID() { //Gets the ID.
			return ID;
		}

		public void setID(int iD) { //Sets the ID.
			ID = iD;
		}

		public boolean isStatic() { //Gets the isStaic.
			return isStatic;
		}

		public void setStatic(boolean isStatic) { //Sets the isStatic.
			this.isStatic = isStatic;
		}

		public ImageView getImage() { //Gets the image.
			return image;
		}

		public void setImage(ImageView image) { //Sets the image.
			this.image = image;
		}

		public String getFeature() { //Gets the feature.
			return feature;
		}

		public void setFeature(String feature) { //Sets the feature.
			this.feature = feature;
		}
		
		public boolean movableToRight(GridPane gridpane, ArrayList<Tile> tiles) { //Checks the right side of the tile and returns a boolean value properly then clears the ArrayList.
			ArrayList<Tile> freeTiles = new ArrayList<>();
			for(int i = 0; i < tiles.size(); i++) {
				if(tiles.get(i).getProperty().equals("Free")) { //Finds the ones that are free in here.
					freeTiles.add(tiles.get(i));

				}
			}
			for(int i = 0; i < freeTiles.size(); i++) { //Checks it in here.
				if(gridpane.getColumnIndex(freeTiles.get(i).getImage()) == gridpane.getColumnIndex(image) +1 && 
						gridpane.getRowIndex(freeTiles.get(i).image) == gridpane.getRowIndex(image) &&
						gridpane.getColumnIndex(image) != 3) {
					freeTiles.clear();
					return true;
				}
			}
			freeTiles.clear();
			return false;
		}
		
		public boolean movableToLeft(GridPane gridpane, ArrayList<Tile> tiles) { //Checks the left side of the tile and returns a boolean value properly then clears the ArrayList.
			ArrayList<Tile> freeTiles = new ArrayList<>();
			for(int i = 0; i < tiles.size(); i++) {
				if(tiles.get(i).getProperty().equals("Free")) { //Finds the ones that are free in here.
					freeTiles.add(tiles.get(i));
				}
			}
			for(int i = 0; i < freeTiles.size(); i++) { //Checks it in here.
				if(gridpane.getColumnIndex(freeTiles.get(i).getImage()) == gridpane.getColumnIndex(image) - 1 && 
						gridpane.getRowIndex(freeTiles.get(i).image) == gridpane.getRowIndex(image) &&
						gridpane.getColumnIndex(image) != 0) {
					freeTiles.clear();
					return true;					
				}
			}
			freeTiles.clear();
			return false;
		} 
		
		public boolean movableToDown(GridPane gridpane, ArrayList<Tile> tiles) { //Checks the bottom side of the tile and returns a boolean value properly then clears the ArrayList.
			ArrayList<Tile> freeTiles = new ArrayList<>();
			for(int i = 0; i < tiles.size(); i++) {
				if(tiles.get(i).getProperty().equals("Free")) { //Finds the ones that are free in here.
					freeTiles.add(tiles.get(i));
				}
			}
			for(int i = 0; i < freeTiles.size(); i++) { //Checks it in here.
				if(gridpane.getColumnIndex(freeTiles.get(i).getImage()) == gridpane.getColumnIndex(image) && 
						gridpane.getRowIndex(freeTiles.get(i).image) == gridpane.getRowIndex(image)  + 1 &&
						gridpane.getRowIndex(image) != 3) {	
					freeTiles.clear();
					return true;
				}
			}
			freeTiles.clear();
			return false;
		} 
		
		public boolean movableToUp(GridPane gridpane, ArrayList<Tile> tiles) { //Checks the upper side of the tile and returns a boolean value properly then clears the ArrayList.
			ArrayList<Tile> freeTiles = new ArrayList<>();
			for(int i = 0; i < tiles.size(); i++) {
				if(tiles.get(i).getProperty().equals("Free")) {
					freeTiles.add(tiles.get(i));
				}
			}
			for(int i = 0; i < freeTiles.size(); i++) { //Checks it in here.
				if(gridpane.getColumnIndex(freeTiles.get(i).getImage()) == gridpane.getColumnIndex(image) && 
						gridpane.getRowIndex(freeTiles.get(i).image) == gridpane.getRowIndex(image)  - 1 &&
						gridpane.getRowIndex(image) != 0) {	
					freeTiles.clear();
					return true;
				}
			}
			freeTiles.clear();
			return false;
		} 
	}