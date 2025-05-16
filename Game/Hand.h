#pragma once
#include <tuple>

#include "../Models/Move.h"
#include "../Models/Response.h"
#include "Board.h"

// methods for hands
class Hand
{
  public:
    Hand(Board *board) : board(board)
    {
    }
    // Определяет координаты ячейки куда нажал игрок или событие, если нажата соответствующая кнопка
    tuple<Response, POS_T, POS_T> get_cell() const
    {
        SDL_Event windowEvent;
        Response resp = Response::OK;
        int x = -1, y = -1;
        int xc = -1, yc = -1;
        while (true)
        {
            if (SDL_PollEvent(&windowEvent))
            {
                switch (windowEvent.type)
                {
                // Нажатие на кнопку закрытия окна
                case SDL_QUIT:
                    resp = Response::QUIT;
                    break;
                // Щелчок мыши
                case SDL_MOUSEBUTTONDOWN:
                    x = windowEvent.motion.x;
                    y = windowEvent.motion.y;
                    xc = int(y / (board->H / 10) - 1);
                    yc = int(x / (board->W / 10) - 1);
                    // Нажатие на кнопку "Назад"
                    if (xc == -1 && yc == -1 && board->history_mtx.size() > 1)
                    {
                        resp = Response::BACK;
                    }
                    // Нажатие на кнопку "Повтор"
                    else if (xc == -1 && yc == 8)
                    {
                        resp = Response::REPLAY;
                    }
                    // Нажатие на ячейку поля
                    else if (xc >= 0 && xc < 8 && yc >= 0 && yc < 8)
                    {
                        resp = Response::CELL;
                    }
                    // Нажатие на свободную область
                    else
                    {
                        xc = -1;
                        yc = -1;
                    }
                    break;
                // Изменение размера окна
                case SDL_WINDOWEVENT:
                    if (windowEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    {
                        board->reset_window_size();
                        break;
                    }
                }
                // Выполнено действие меняющее состояние игры
                if (resp != Response::OK)
                    break;
            }
        }
        return {resp, xc, yc};
    }

    Response wait() const
    {
        SDL_Event windowEvent;
        Response resp = Response::OK;
        while (true)
        {
            if (SDL_PollEvent(&windowEvent))
            {
                switch (windowEvent.type)
                {
                case SDL_QUIT:
                    resp = Response::QUIT;
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    board->reset_window_size();
                    break;
                case SDL_MOUSEBUTTONDOWN: {
                    int x = windowEvent.motion.x;
                    int y = windowEvent.motion.y;
                    int xc = int(y / (board->H / 10) - 1);
                    int yc = int(x / (board->W / 10) - 1);
                    if (xc == -1 && yc == 8)
                        resp = Response::REPLAY;
                }
                break;
                }
                if (resp != Response::OK)
                    break;
            }
        }
        return resp;
    }

  private:
    Board *board;
};
