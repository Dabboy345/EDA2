# Welcome to our game 

Hello, we are Noel, Arlet, and Sushant. We are group 14 from Practice 102. The principle idea of our game is that we are under a simulation and we don't know it and as we go forward in the game we start to notice anomalies and your objective will be to wake up from this simulation. Our game consists of four maps. There are many skills that you can try. Hope you have fun!
- Our Data structures
    - Skill
    ```C
    typedef struct { //Our data stucture for the skills
            char name[MAX_NAME];
            char description[MAX_TXT];
            int of_def; //1 for offensive, 0 for deffensive
            int dmg_skll;// 10-35
            char modifier[MAX_NAME];
            int stats_plyr[3]; //dmg(0), def(1), hp(2)
            /*int dmg_plyr; 1-2       int def_plyr; 0 - 8       int hp_plyr; 25 - 50 */
    } Skill;
    ```
  - Character
    ```C
        typedef struct{ //This is our data structures for the character
            char name[MAX_NAME];
            int stats[3];//dmg(0), def(1), hp(2)
            //int dmg; 12 - 32      int def; 0 - 32       int hp; 100 - 200
            Skill skill[4];
        }Character;
    ```
  - Enemy
    ```C
    typedef struct{ //This is our data structures for the Enemy
      char name[MAX_NAME];
      int dmg;
      int def;
      int hp;
      Skill skill[4];
    } Enemy;
  ```
  - Option 
    ```C
    typedef struct{
        char description[MAX_TXT];
        char pre_txt[MAX_TXT];
        Enemy enemy[3];
        char post_txt[MAX_TXT];
    }Option;
  ```
  

  
    
