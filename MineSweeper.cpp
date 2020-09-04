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
                array1[i][j] = '*';
                array2[i][j] = 0;
            }
        }
        flagScore = 0;
        score = 0;
    }
    ~Board() {}
    void printBoard() {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                std::cout << array1[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void printAnsBoard() {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                std::cout << array2[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void insertBomb() {
        for (int i=0; i<Bomb; ++i) {
            srand(time(0));
            int t = rand() % N;
            int x = rand() % N;
            while (array2[t][x] == B) {
                t = rand() % N;
                x = rand() % N;
            }
            array2[t][x] = B;
        }
    }

    void findAdj() {
            for (int i=0; i<N; ++i) {
                for (int j=0; j<N; ++j) {
                    if (array2[i][j] == B) {
                        continue;
                    }
                    int count = 0;
                    if ((i == 0 && j == N-1) || (i == 0 && j == 0) || (i== N-1 && j == 0) || (i == N-1 && j == N-1)) {
                        if (i == 0 && j == N-1) {
                            if (array2[i+1][j] == B) 
                                ++count;
                            if (array2[i][j-1] == B)
                                ++count;
                            if (array2[i+1][j-1] == B)
                                ++count;
                        } else if (i == 0 && j == 0) {
                            if (array2[i+1][j] == B) 
                                ++count;
                            if (array2[i][j+1] == B)
                                ++count;
                            if (array2[i+1][j+1] == B)
                                ++count;
                        } else if (i== N-1 && j == 0) {
                            if (array2[i-1][j] == B) 
                                ++count;
                            if (array2[i][j+1] == B)
                                ++count;
                            if (array2[i-1][j+1] == B)
                                ++count;
                        } else if (i == N-1 && j == N-1) {
                            if (array2[i-1][j] == B) 
                                ++count;
                            if (array2[i][j-1] == B)
                                ++count;
                            if (array2[i-1][j-1] == B)
                                ++count;
                        }
                    } else if (i == 0 || j == 0 || i == N-1 || j == N-1) {
                        switch(i) {
                            case 0:
                                if (array2[i][j-1] == B)
                                    ++count;
                                if (array2[i][j+1] == B)
                                    ++count;
                                if (array2[i+1][j-1] == B)
                                    ++count;
                                if (array2[i+1][j] == B)
                                    ++count;
                                if (array2[i+1][j+1] == B)
                                    ++count;
                                break;

                            case N-1:
                                if (array2[i][j-1] == B)
                                    ++count;
                                if (array2[i][j+1] == B)
                                    ++count;
                                if (array2[i-1][j-1] == B)
                                    ++count;
                                if (array2[i-1][j] == B)
                                    ++count;
                                if (array2[i-1][j+1] == B)
                                    ++count;
                                break;
                        }

                        switch(j) {
                            case 0:
                            if (array2[i+1][j] == B)
                                    ++count;
                                if (array2[i-1][j] == B)
                                    ++count;
                                if (array2[i-1][j+1] == B)
                                    ++count;
                                if (array2[i][j+1] == B)
                                    ++count;
                                if (array2[i+1][j+1] == B)
                                    ++count;
                                break;

                            case N-1:
                            if (array2[i+1][j] == B)
                                    ++count;
                                if (array2[i-1][j] == B)
                                    ++count;
                                if (array2[i-1][j-1] == B)
                                    ++count;
                                if (array2[i][j-1] == B)
                                    ++count;
                                if (array2[i+1][j-1] == B)
                                    ++count;
                                break;
                        }

                } else {
                    for (int p = j-1; p<j+2; ++p) {
                        if (array2[i+1][p] == B) 
                            ++count;
                    }

                    for (int p = j-1; p<j+2; ++p) {
                        if (array2[i-1][p] == B) 
                            ++count;
                    }

                    if (array2[i][j+1] == B) 
                        ++count;

                    if (array2[i][j-1] == B) 
                        ++count;
                }
                array2[i][j] = count;
            }
        }
    }

    void printScore() {
            std::cout << "Number of Flags: " << flagScore << std::endl;
            std::cout << "Score: " << score << std::endl;
    }
    
    void firstMove() {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                if (array2[i][j] == 0) {
                    array1[i][j] == '0';
                    break;
                }
            }
        }
    }

    char array1[N][N];
    int array2[N][N];

    int flagScore, score;

};


class Cell {
    public:
        Cell() {}
        void setCell(Board board, int size) {
            std::cout << "Enter your move (row coloumn) (only use numbers seperated by space):" << std::endl;
            std::cin >> x >> y;
            while (x<1 || x>size || y<1 || y>size) {
                std::cout << "Invalid input. Input again:" << std::endl;
                std::cin >> x >> y;
            } 

            x -= 1;
            y -= 1;

            display = board.array1[x][y];
            ans = board.array2[x][y];

            while (display != '*' && display != 'F') {
                std::cout << "This is already revealed. Input again:" << std::endl;
                std::cin >> x >> y;
            }
            x -= 1;
            y -= 1;

            flags = 0;
            reveal = 0;
            display = board.array1[x][y];
            ans = board.array2[x][y];
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

        void copyBoard(Board &board1) {
            board1.array1[x][y] = display;
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
        board1.printScore();
        cell1.~Cell();
    }


    board1.printAnsBoard();

    return 0;
}
