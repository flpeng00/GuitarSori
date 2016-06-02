#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>
#define pi M_PI

long bitreverse(long i, long size);
long bruun_reverse(long i, long sizze);
void dif_butterfly(double * data, long size);
void inverse_dit_butterfly(double * data, long size);
void unshuffle(double * data, long size);
void realize(double * data, long size);
void unrealize(double * data, long size);
void fft(double * data, long size);
void ifft(double * data, long size);
void realfft_packed(double * data, long size);
void irealfft_packed(double * data, long size);
void realfft_bruun(double * data, long size);
void realfft_bruun_unshuffled(double * data, long size);
void realfft_split(double * data, long n);
void realfft_split_unshuffled(double * data, long n);
void irealfft_split(double * data, long n);
void realfft_radix2(double * data, long n);
void realfft_radix2_unshuffled(double * data, long n);
