#include "global.h"

SDL_Surface *screen;
SDL_Event event;

SDL_Color color;

SDL_Surface *menuImage;
SDL_Surface *mapImage;
SDL_Surface *icon;

SDL_Surface *item_sprite;
SDL_Surface *enemy_sprite;
SDL_Surface *fire_sprite;
SDL_Surface *player_sprite;

TTF_Font *font;
SDL_AudioSpec audioFmt;
struct audioSample sounds[NUM_SOUNDS];

bool repeatAudio;
int audioVol;

SDL_Thread *threadplayer;
SDL_Thread *threadenemy1;
SDL_Thread *threadenemy2;
SDL_Thread *threadenemy3;
SDL_Thread *threadtext;

Player *player;
Enemy *enemy;
Enemy *enemy2;
Enemy *enemy3;

Map map(13,11);

void displayImage(SDL_Surface *image, int x, int y)
{
    SDL_Rect src, dest;
    src.x = 0;
    src.y = 0;
    src.w = image->w;
    src.h = image->h;

    dest.x = x;
    dest.y = y;
    dest.w = image->w;
    dest.h = image->h;

    SDL_BlitSurface(image, &src, screen, &dest);
}

void displaySpriteImage(SDL_Surface *sprite, int x, int y, int dx, int dy, int sprite_size, int colorkey)
{
    SDL_Rect src, dest;
    src.x = dx;
    src.y = dy;
    src.w = sprite_size;
    src.h = sprite_size;

    dest.x = x;
    dest.y = y;
    dest.w = sprite_size;
    dest.h = sprite_size;

    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_BlitSurface(sprite, &src, screen, &dest);
}

void drawText(string texto, SDL_Surface* dst, int x, int y, SDL_Color color)
{

  /*SDL_Surface* src = TTF_RenderText_Blended(font, texto, color);
  SDL_Rect dst_rect = {x, y, 0, 0};

  SDL_BlitSurface(src, NULL, dst, &dst_rect);

  SDL_FreeSurface(src);*/
}


void mixaudio(void *unused, Uint8 *stream, int len)
{
    int i;
    Uint32 amount;

    for ( i=0; i<NUM_SOUNDS; ++i ) {
        amount = (sounds[i].dlen-sounds[i].dpos);
        if ( amount > len ) {
            amount = len;
        }
        SDL_MixAudio(stream, &sounds[i].data[sounds[i].dpos], amount, audioVol);
        sounds[i].dpos += amount;

        if(repeatAudio && sounds[i].dpos>=sounds[i].dlen){
            sounds[i].dpos = 0;
        }
    }
}

void repeatSound(bool loop)
{
    repeatAudio = loop;
}

void setSoundVolume(int vol)
{
    audioVol = vol;

    if(audioVol<0) audioVol = 0;
    if(audioVol>SDL_MIX_MAXVOLUME) audioVol = SDL_MIX_MAXVOLUME;
}

void playSound(string file, bool loop, int vol)
{
    /*int index;
    SDL_AudioSpec wave;
    Uint8 *data;
    Uint32 dlen;
    SDL_AudioCVT cvt;
    repeatSound(loop);
    setSoundVolume(vol);

    // procura por um slot de som vago (ou finalizado) 
    for ( index=0; index<NUM_SOUNDS; ++index ) {
        if ( sounds[index].dpos == sounds[index].dlen ) {
            break;
        }
    }
    if ( index == NUM_SOUNDS )
        return;

// carrega o arquivo de som e o converte para 16-bit stereo com 22Khz
    if ( SDL_LoadWAV(file, &wave, &data, &dlen) == NULL ) {
        fprintf(stderr, "Não foi possível carregar %s: %s\n", file, SDL_GetError());
        return;
    }
    //SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq, AUDIO_S16,   2, 22050);
    SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq, AUDIO_S16, 1, SOUND_FREQUENCY );
    cvt.buf = (Uint8 *)malloc(dlen*cvt.len_mult);
    memcpy(cvt.buf, data, dlen);
    cvt.len = dlen;
    SDL_ConvertAudio(&cvt);
    SDL_FreeWAV(data);

// Coloca os dados de som no slot (ele começa a tocar imediatamente) 
    if ( sounds[index].data ) {
        free(sounds[index].data);
    }
    SDL_LockAudio();
    sounds[index].data = cvt.buf;
    sounds[index].dlen = cvt.len_cvt;
    sounds[index].dpos = 0;
    SDL_UnlockAudio();*/
}

