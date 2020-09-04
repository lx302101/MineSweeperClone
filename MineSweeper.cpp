#include <iostream>
#include <ctime>
#include <cstdlib>

#define N 9 //Size of Board is N*N
#define Bomb 10 //Number of Bombs
#define B 9 //What bomb is represented in int array

class Board {
    public:
    Board() {
        for (int i=0; i<N; ++i) { 
            for (int j=0; j<N; ++j) {
                displayBoard[i][j] = '*';
                ansBoard[i][j] = 0;
            }
        }
        flagScore = 0;
        score = 0;
    }
    ~Board() {}
    void printBoard() {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                std::cout << displayBoard[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void printAnsBoard() {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                std::cout << ansBoard[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void insertBomb() {
        for (int i=0; i<Bomb; ++i) {
            srand(time(0));
            int t = rand() % N;
            int x = rand() % N;
            while (ansBoard[t][x] == B) {
                t = rand() % N;
                x = rand() % N;
            }
            ansBoard[t][x] = B;
        }
    }

    void findAdj() {
            for (int i=0; i<N; ++i) {
                for (int j=0; j<N; ++j) {
                    if (ansBoard[i][j] == B) {
                        continue;
                    }
                    int count = 0;
                    if ((i == 0 && j == N-1) || (i == 0 && j == 0) || (i== N-1 && j == 0) || (i == N-1 && j == N-1)) { //if not side or corner
                        if (i == 0 && j == N-1) {
                            if (ansBoard[i+1][j] == B) 
                                ++count;
                            if (ansBoard[i][j-1] == B)
                                ++count;
                            if (ansBoard[i+1][j-1] == B)
                                ++count;
                        } else if (i == 0 && j == 0) {
                            if (ansBoard[i+1][j] == B) 
                                ++count;
                            if (ansBoard[i][j+1] == B)
                                ++count;
                            if (ansBoard[i+1][j+1] == B)
                                ++count;
                        } else if (i== N-1 && j == 0) {
                            if (ansBoard[i-1][j] == B) 
                                ++count;
                            if (ansBoard[i][j+1] == B)
                                ++count;
                            if (ansBoard[i-1][j+1] == B)
                                ++count;
                        } else if (i == N-1 && j == N-1) {
                            if (ansBoard[i-1][j] == B) 
                                ++count;
                            if (ansBoard[i][j-1] == B)
                                ++count;
                            if (ansBoard[i-1][j-1] == B)
                                ++count;
                        }
                    } else if (i == 0 || j == 0 || i == N-1 || j == N-1) { //if side
                        switch(i) {
                            case 0:
                                if (ansBoard[i][j-1] == B)
                                    ++count;
                                if (ansBoard[i][j+1] == B)
                                    ++count;
                                if (ansBoard[i+1][j-1] == B)
                                    ++count;
                                if (ansBoard[i+1][j] == B)
                                    ++count;
                                if (ansBoard[i+1][j+1] == B)
                                    ++count;
                                break;

                            case N-1:
                                if (ansBoard[i][j-1] == B)
                                    ++count;
                                if (ansBoard[i][j+1] == B)
                                    ++count;
                                if (ansBoard[i-1][j-1] == B)
                                    ++count;
                                if (ansBoard[i-1][j] == B)
                                    ++count;
                                if (ansBoard[i-1][j+1] == B)
                                    ++count;
                                break;
                        }

                        switch(j) { 
                            case 0:
                            if (ansBoard[i+1][j] == B)
                                    ++count;
                                if (ansBoard[i-1][j] == B)
                                    ++count;
                                if (ansBoard[i-1][j+1] == B)
                                    ++count;
                                if (ansBoard[i][j+1] == B)
                                    ++count;
                                if (ansBoard[i+1][j+1] == B)
                                    ++count;
                                break;

                            case N-1:
                            if (ansBoard[i+1][j] == B)
                                    ++count;
                                if (ansBoard[i-1][j] == B)
                                    ++count;
                                if (ansBoard[i-1][j-1] == B)
                                    ++count;
                                if (ansBoard[i][j-1] == B)
                                    ++count;
                                if (ansBoard[i+1][j-1] == B)
                                    ++count;
                                break;
                        }

                } else { //if corner
                    for (int p = j-1; p<j+2; ++p) {
                        if (ansBoard[i+1][p] == B) 
                            ++count;
                    }

                    for (int p = j-1; p<j+2; ++p) {
                        if (ansBoard[i-1][p] == B) 
                            ++count;
                    }

                    if (ansBoard[i][j+1] == B) 
                        ++count;

                    if (ansBoard[i][j-1] == B) 
                        ++count;
                }
                ansBoard[i][j] = count;
            }
        }
    }

    void printScore(bool &isGame) {
            std::cout << "Number of Flags: " << flagScore << std::endl;
            std::cout << "Score: " << score << std::endl;
            if (score == N*N - Bomb + 1) {
                std::cout << "You win!" << std::endl;
                isGame = false;
            }
    }
    
    void firstMove() {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                if (ansBoard[i][j] == 0) {
                    displayBoard[i][j] == '0';
                    break;
                }
            }
        }
    }

    char displayBoard[N][N];
    int ansBoard[N][N];

    int flagScore, score;

};


class Cell {
    public:
        Cell() {}
        void setCell(Board board) {
            std::cout << "Enter your move (row coloumn) (only use numbers seperated by space):" << std::endl;
            std::cin >> x >> y;
            while (x<1 || x>N || y<1 || y>N) {
                std::cout << "Invalid input. Input again:" << std::endl;
                std::cin >> x >> y;
            } 

            x -= 1;
            y -= 1;

            display = board.displayBoard[x][y];
            ans = board.ansBoard[x][y];

            while (display != '*' && display != 'F') {
                std::cout << "This is already revealed. Input again:" << std::endl;
                std::cin >> x >> y;
            }
            x -= 1;
            y -= 1;

            flags = 0;
            reveal = 0;
            display = board.displayBoard[x][y];
            ans = board.ansBoard[x][y];
        }

        ~Cell() {}

        void userTask(bool &isGame) {
            int t;
            std::cout << "What would you like to do?" << std::endl;
            std::cout << "1. Reveal Cell" << std::endl;
            if (display == 'F')
                std::cout << "2. Remove Flag" << std::endl;
            else 
                std::cout << "2. Flag" << std::endl;
            std::cout << "3. Nothing" << std::endl;
            std::cin >> t;
            switch (t) {
                case 1:
                    if (display == 'F') {
                        int i;
                        std::cout << "This position is flagged. Are you sure you want to reveal?" << std::endl;
                        std::cout << "1. Yes  2. No " << std::endl;
                        std::cin >> i;
                        if (i == 1) {
                            if (ans == B) display = 'B'; 
                            else display = ans + 48;
                            if (display == 'B') {
                                std::cout << "You hit a bomb! Game Over" << std::endl;
                                isGame = false;
                            }
                            ++reveal;   
                        } else 
                            break;
                    } else {
                        if (ans == B) display = 'B'; 
                        else display = ans + 48;
                        if (display == 'B') {
                            std::cout << "You hit a bomb! Game Over" << std::endl;
                            isGame = false;
                        }
                        ++reveal;
                    }
                    break;

                case 2:
                    if (display == 'F') {
                        display = '*';
                        --flags;    
                    } else {  
                        display = 'F';
                        ++flags;
                    } 
                    break;
            }
        }

        void copyBoard(Board &board1) { //Copy scores to board
            board1.displayBoard[x][y] = display;
            board1.flagScore += flags;
            board1.score += reveal;
        } 

    private:
        int x, y, flags, reveal;
        char display;
        int ans;

};



int main() {
    Board board1;
    board1.insertBomb();
    board1.findAdj();

    bool isGame = true;

    board1.firstMove();
    board1.printBoard();


    while(isGame == true) {
        Cell cell1;
        cell1.setCell(board1);
        cell1.userTask(isGame);
        cell1.copyBoard(board1);
        board1.printBoard();
        board1.printScore(isGame);
        cell1.~Cell();
    }


    board1.printAnsBoard();
    std::cout << "9 is where the bomb is" << std::endl;

    return 0;
}
