/*


This header contains consts used to keep track of position pieces on board and
other consts.

*/
#pragma once

const int a = 0;
const int b = 1;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 5;
const int g = 6;
const int h = 7;

const bool white = true;
const bool black = false;

const int pawn = 1;
const int rook = 2;
const int bishop = 3;
const int horse = 4;
const int queen = 5;
const int king = 6;

const int player = 0;
const int enemy = 1;

const int screen_width = 850;
const int screen_height = 650;

const int padding = 10;

const int cellW = (screen_width - 2 * padding) / 8;
const int cellH = (screen_height - 2 * padding) / 8;
