#include <iostream>
#include <pthread.h>
#include <atomic>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>  // For usleep

using namespace std;

const int BOARD_SIZE = 19; // Board size
const int SQUARE_SIZE = 20; // Size of each square on the board
const int WINDOW_SIZE = BOARD_SIZE * SQUARE_SIZE;

// SDL Window and Renderer
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

// Game Board (using basic 2D array)
int board[BOARD_SIZE][BOARD_SIZE] = {0};

// Player positions
int player1_x = 0, player1_y = 0;
int player2_x = BOARD_SIZE - 1, player2_y = BOARD_SIZE - 1;

// Player scores
atomic<int> player1_score(0);
atomic<int> player2_score(0);

// Player message queues (as atomic flags instead of mutexes)
atomic<bool> player1Moved(false);
atomic<bool> player2Moved(false);

// Initialize SDL
void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Failed to initialize SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    window = SDL_CreateWindow("Multiplayer Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE, WINDOW_SIZE, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!window || !renderer) {
        cout << "Failed to create window or renderer: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
}

// Draw the Board
void drawBoard() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw board grid
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            SDL_Rect rect = {i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE};
            SDL_RenderDrawRect(renderer, &rect);
            
            // Draw items on the board
            if (board[i][j] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for items
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    // Draw Player 1
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for Player 1
    SDL_Rect player1_rect = {player1_x * SQUARE_SIZE, player1_y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE};
    SDL_RenderFillRect(renderer, &player1_rect);

    // Draw Player 2
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for Player 2
    SDL_Rect player2_rect = {player2_x * SQUARE_SIZE, player2_y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE};
    SDL_RenderFillRect(renderer, &player2_rect);

    SDL_RenderPresent(renderer);
}

// Player Thread Function (handles movements)
void* playerThread(void* arg) {
    while (true) {
        // Simulate player move
        if (*(int*)arg == 1) {
            player1Moved.store(true);
        } else {
            player2Moved.store(true);
        }

        usleep(500000); // Simulate delay (500ms)
    }
    return nullptr;
}

// Handle player movement and item collection
void handlePlayerMovement(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        bool itemCollected = false;

        // Player 1 controls (Arrow keys)
        if (event.key.keysym.sym == SDLK_UP && player1_y > 0) player1_y--;
        else if (event.key.keysym.sym == SDLK_DOWN && player1_y < BOARD_SIZE - 1) player1_y++;
        else if (event.key.keysym.sym == SDLK_LEFT && player1_x > 0) player1_x--;
        else if (event.key.keysym.sym == SDLK_RIGHT && player1_x < BOARD_SIZE - 1) player1_x++;

        // Check if Player 1 collected an item
        if (board[player1_x][player1_y] == 1) {
            board[player1_x][player1_y] = 0;
            player1_score.fetch_add(10); // Increment score atomically
            itemCollected = true;
        }

        // Player 2 controls (WASD keys)
        if (event.key.keysym.sym == SDLK_w && player2_y > 0) player2_y--;
        else if (event.key.keysym.sym == SDLK_s && player2_y < BOARD_SIZE - 1) player2_y++;
        else if (event.key.keysym.sym == SDLK_a && player2_x > 0) player2_x--;
        else if (event.key.keysym.sym == SDLK_d && player2_x < BOARD_SIZE - 1) player2_x++;

        // Check if Player 2 collected an item
        if (board[player2_x][player2_y] == 1) {
            board[player2_x][player2_y] = 0;
            player2_score.fetch_add(10); // Increment score atomically
            itemCollected = true;
        }
    }
}

// Main thread function to process messages
void* processMessages(void* arg) {
    while (true) {
        if (player1Moved.load()) {
            cout << "Player 1 moved! Score: " << player1_score.load() << endl;
            player1Moved.store(false); // Reset flag
        }

        if (player2Moved.load()) {
            cout << "Player 2 moved! Score: " << player2_score.load() << endl;
            player2Moved.store(false); // Reset flag
        }

        usleep(100000); // Sleep for 100ms
    }
    return nullptr;
}

// Main Function
int main() {
    srand(time(0));
    initSDL();

    // Place some items randomly on the board
    for (int i = 0; i < 50; ++i) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        board[x][y] = 1;
    }

    // Create player threads
    int player1ID = 1;
    int player2ID = 2;
    pthread_t player1, player2;

    pthread_create(&player1, nullptr, playerThread, &player1ID);
    pthread_create(&player2, nullptr, playerThread, &player2ID);

    // Start message processing thread
    pthread_t messageThread;
    pthread_create(&messageThread, nullptr, processMessages, nullptr);

    // Main game loop
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            handlePlayerMovement(event);
        }
        drawBoard();
        SDL_Delay(100); // Refresh rate
    }

    // Once the game ends, print final scores
    cout << "Game Over!" << endl;
    cout << "Player 1 Final Score: " << player1_score.load() << endl;
    cout << "Player 2 Final Score: " << player2_score.load() << endl;

    // Wait for threads to finish
    pthread_join(player1, nullptr);
    pthread_join(player2, nullptr);
    pthread_join(messageThread, nullptr);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

