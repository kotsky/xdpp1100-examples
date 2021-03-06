/*
 * user_ptc_temperature_lut.h
 *
 *  Created on: Aug 30, 2019
 *      Author:
 */

#ifndef USER_PTC_TEMPERATURE_LUT_H_
#define USER_PTC_TEMPERATURE_LUT_H_

#include <stdint.h>              /** uint*_t */

/**
 * Look up table for ntc temperature decode.  Index is in adc_codes, values are temperature C
 * User can set their NTC based on datasheet as a look up table below:
 */
const int16_t user_ptc_temp_lut[512] =
{
	-40      ,           //degrees C adc_code = 0
	-40      ,           //degrees C adc_code = 1
	-40      ,           //degrees C adc_code = 2
	-40      ,           //degrees C adc_code = 3
	-40      ,           //degrees C adc_code = 4
	-40      ,           //degrees C adc_code = 5
	-40      ,           //degrees C adc_code = 6
	-40      ,           //degrees C adc_code = 7
	-40      ,           //degrees C adc_code = 8
	-40      ,           //degrees C adc_code = 9
	-40      ,           //degrees C adc_code = 10
	-40      ,           //degrees C adc_code = 11
	-40      ,           //degrees C adc_code = 12
	-40      ,           //degrees C adc_code = 13
	-40      ,           //degrees C adc_code = 14
	-40      ,           //degrees C adc_code = 15
	-40      ,           //degrees C adc_code = 16
	-40      ,           //degrees C adc_code = 17
	-40      ,           //degrees C adc_code = 18
	-40      ,           //degrees C adc_code = 19
	-40      ,           //degrees C adc_code = 20
	-40      ,           //degrees C adc_code = 21
	-40      ,           //degrees C adc_code = 22
	-40      ,           //degrees C adc_code = 23
	-40      ,           //degrees C adc_code = 24
	-40      ,           //degrees C adc_code = 25
	-40      ,           //degrees C adc_code = 26
	-40      ,           //degrees C adc_code = 27
	-40      ,           //degrees C adc_code = 28
	-40      ,           //degrees C adc_code = 29
	-40      ,           //degrees C adc_code = 30
	-40      ,           //degrees C adc_code = 31
	-40      ,           //degrees C adc_code = 32
	-40      ,           //degrees C adc_code = 33
	-40      ,           //degrees C adc_code = 34
	-40      ,           //degrees C adc_code = 35
	-40      ,           //degrees C adc_code = 36
	-40      ,           //degrees C adc_code = 37
	-40      ,           //degrees C adc_code = 38
	-40      ,           //degrees C adc_code = 39
	-40      ,           //degrees C adc_code = 40
	-40      ,           //degrees C adc_code = 41
	-40      ,           //degrees C adc_code = 42
	-40      ,           //degrees C adc_code = 43
	-40      ,           //degrees C adc_code = 44
	-40      ,           //degrees C adc_code = 45
	-40      ,           //degrees C adc_code = 46
	-40      ,           //degrees C adc_code = 47
	-40      ,           //degrees C adc_code = 48
	-40      ,           //degrees C adc_code = 49
	-40      ,           //degrees C adc_code = 50
	-40      ,           //degrees C adc_code = 51
	-40      ,           //degrees C adc_code = 52
	-40      ,           //degrees C adc_code = 53
	-40      ,           //degrees C adc_code = 54
	-40      ,           //degrees C adc_code = 55
	-40      ,           //degrees C adc_code = 56
	-40      ,           //degrees C adc_code = 57
	-40      ,           //degrees C adc_code = 58
	-40      ,           //degrees C adc_code = 59
	-40      ,           //degrees C adc_code = 60
	-40      ,           //degrees C adc_code = 61
	-40      ,           //degrees C adc_code = 62
	-40      ,           //degrees C adc_code = 63
	-40      ,           //degrees C adc_code = 64
	-40      ,           //degrees C adc_code = 65
	-40      ,           //degrees C adc_code = 66
	-40      ,           //degrees C adc_code = 67
	-40      ,           //degrees C adc_code = 68
	-40      ,           //degrees C adc_code = 69
	-40      ,           //degrees C adc_code = 70
	-40      ,           //degrees C adc_code = 71
	-40      ,           //degrees C adc_code = 72
	-40      ,           //degrees C adc_code = 73
	-40      ,           //degrees C adc_code = 74
	-40      ,           //degrees C adc_code = 75
	-40      ,           //degrees C adc_code = 76
	-40      ,           //degrees C adc_code = 77
	-40      ,           //degrees C adc_code = 78
	-40      ,           //degrees C adc_code = 79
	-40      ,           //degrees C adc_code = 80
	-40      ,           //degrees C adc_code = 81
	-40      ,           //degrees C adc_code = 82
	-40      ,           //degrees C adc_code = 83
	-40      ,           //degrees C adc_code = 84
	-40      ,           //degrees C adc_code = 85
	-40      ,           //degrees C adc_code = 86
	-40      ,           //degrees C adc_code = 87
	-40      ,           //degrees C adc_code = 88
	-40      ,           //degrees C adc_code = 89
	-40      ,           //degrees C adc_code = 90
	-40      ,           //degrees C adc_code = 91
	-40      ,           //degrees C adc_code = 92
	-40      ,           //degrees C adc_code = 93
	-40      ,           //degrees C adc_code = 94
	-40      ,           //degrees C adc_code = 95
	-40      ,           //degrees C adc_code = 96
	-40      ,           //degrees C adc_code = 97
	-40      ,           //degrees C adc_code = 98
	-40      ,           //degrees C adc_code = 99
	-40      ,           //degrees C adc_code = 100
	-40      ,           //degrees C adc_code = 101
	-40      ,           //degrees C adc_code = 102
	-40      ,           //degrees C adc_code = 103
	-40      ,           //degrees C adc_code = 104
	-40      ,           //degrees C adc_code = 105
	-40      ,           //degrees C adc_code = 106
	-40      ,           //degrees C adc_code = 107
	-40      ,           //degrees C adc_code = 108
	-40      ,           //degrees C adc_code = 109
	-40      ,           //degrees C adc_code = 110
	-40      ,           //degrees C adc_code = 111
	-40      ,           //degrees C adc_code = 112
	-40      ,           //degrees C adc_code = 113
	-40      ,           //degrees C adc_code = 114
	-40      ,           //degrees C adc_code = 115
	-40      ,           //degrees C adc_code = 116
	-40      ,           //degrees C adc_code = 117
	-40      ,           //degrees C adc_code = 118
	-40      ,           //degrees C adc_code = 119
	-40      ,           //degrees C adc_code = 120
	-40      ,           //degrees C adc_code = 121
	-40      ,           //degrees C adc_code = 122
	-40      ,           //degrees C adc_code = 123
	-40      ,           //degrees C adc_code = 124
	-40      ,           //degrees C adc_code = 125
	-40      ,           //degrees C adc_code = 126
	-40      ,           //degrees C adc_code = 127
	-40      ,           //degrees C adc_code = 128
	-40      ,           //degrees C adc_code = 129
	-40      ,           //degrees C adc_code = 130
	-40      ,           //degrees C adc_code = 131
	-40      ,           //degrees C adc_code = 132
	-40      ,           //degrees C adc_code = 133
	-40      ,           //degrees C adc_code = 134
	-40      ,           //degrees C adc_code = 135
	-40      ,           //degrees C adc_code = 136
	-40      ,           //degrees C adc_code = 137
	-40      ,           //degrees C adc_code = 138
	-40      ,           //degrees C adc_code = 139
	-40      ,           //degrees C adc_code = 140
	-40      ,           //degrees C adc_code = 141
	-40      ,           //degrees C adc_code = 142
	-40      ,           //degrees C adc_code = 143
	-40      ,           //degrees C adc_code = 144
	-40      ,           //degrees C adc_code = 145
	-40      ,           //degrees C adc_code = 146
	-40      ,           //degrees C adc_code = 147
	-40      ,           //degrees C adc_code = 148
	-40      ,           //degrees C adc_code = 149
	-40      ,           //degrees C adc_code = 150
	-40      ,           //degrees C adc_code = 151
	-40      ,           //degrees C adc_code = 152
	-40      ,           //degrees C adc_code = 153
	-40      ,           //degrees C adc_code = 154
	-40      ,           //degrees C adc_code = 155
	-40      ,           //degrees C adc_code = 156
	-40      ,           //degrees C adc_code = 157
	-40      ,           //degrees C adc_code = 158
	-40      ,           //degrees C adc_code = 159
	-40      ,           //degrees C adc_code = 160
	-40      ,           //degrees C adc_code = 161
	-40      ,           //degrees C adc_code = 162
	-40      ,           //degrees C adc_code = 163
	-40      ,           //degrees C adc_code = 164
	-40      ,           //degrees C adc_code = 165
	-40      ,           //degrees C adc_code = 166
	-40      ,           //degrees C adc_code = 167
	-40      ,           //degrees C adc_code = 168
	-40      ,           //degrees C adc_code = 169
	-40      ,           //degrees C adc_code = 170
	-39      ,           //degrees C adc_code = 171
	-39      ,           //degrees C adc_code = 172
	-39      ,           //degrees C adc_code = 173
	-39      ,           //degrees C adc_code = 174
	-39      ,           //degrees C adc_code = 175
	-39      ,           //degrees C adc_code = 176
	-39      ,           //degrees C adc_code = 177
	-39      ,           //degrees C adc_code = 178
	-39      ,           //degrees C adc_code = 179
	-39      ,           //degrees C adc_code = 180
	-39      ,           //degrees C adc_code = 181
	-39      ,           //degrees C adc_code = 182
	-39      ,           //degrees C adc_code = 183
	-39      ,           //degrees C adc_code = 184
	-39      ,           //degrees C adc_code = 185
	-39      ,           //degrees C adc_code = 186
	-39      ,           //degrees C adc_code = 187
	-38      ,           //degrees C adc_code = 188
	-38      ,           //degrees C adc_code = 189
	-38      ,           //degrees C adc_code = 190
	-38      ,           //degrees C adc_code = 191
	-38      ,           //degrees C adc_code = 192
	-38      ,           //degrees C adc_code = 193
	-38      ,           //degrees C adc_code = 194
	-38      ,           //degrees C adc_code = 195
	-38      ,           //degrees C adc_code = 196
	-38      ,           //degrees C adc_code = 197
	-38      ,           //degrees C adc_code = 198
	-38      ,           //degrees C adc_code = 199
	-37      ,           //degrees C adc_code = 200
	-37      ,           //degrees C adc_code = 201
	-37      ,           //degrees C adc_code = 202
	-37      ,           //degrees C adc_code = 203
	-37      ,           //degrees C adc_code = 204
	-37      ,           //degrees C adc_code = 205
	-37      ,           //degrees C adc_code = 206
	-37      ,           //degrees C adc_code = 207
	-37      ,           //degrees C adc_code = 208
	-36      ,           //degrees C adc_code = 209
	-36      ,           //degrees C adc_code = 210
	-36      ,           //degrees C adc_code = 211
	-36      ,           //degrees C adc_code = 212
	-36      ,           //degrees C adc_code = 213
	-36      ,           //degrees C adc_code = 214
	-36      ,           //degrees C adc_code = 215
	-35      ,           //degrees C adc_code = 216
	-35      ,           //degrees C adc_code = 217
	-35      ,           //degrees C adc_code = 218
	-35      ,           //degrees C adc_code = 219
	-35      ,           //degrees C adc_code = 220
	-34      ,           //degrees C adc_code = 221
	-34      ,           //degrees C adc_code = 222
	-34      ,           //degrees C adc_code = 223
	-33      ,           //degrees C adc_code = 224
	-32      ,           //degrees C adc_code = 225
	-31      ,           //degrees C adc_code = 226
	-31      ,           //degrees C adc_code = 227
	-30      ,           //degrees C adc_code = 228
	-29      ,           //degrees C adc_code = 229
	-28      ,           //degrees C adc_code = 230
	-27      ,           //degrees C adc_code = 231
	-27      ,           //degrees C adc_code = 232
	-26      ,           //degrees C adc_code = 233
	-25      ,           //degrees C adc_code = 234
	-24      ,           //degrees C adc_code = 235
	-23      ,           //degrees C adc_code = 236
	-23      ,           //degrees C adc_code = 237
	-22      ,           //degrees C adc_code = 238
	-21      ,           //degrees C adc_code = 239
	-20      ,           //degrees C adc_code = 240
	-19      ,           //degrees C adc_code = 241
	-19      ,           //degrees C adc_code = 242
	-18      ,           //degrees C adc_code = 243
	-17      ,           //degrees C adc_code = 244
	-16      ,           //degrees C adc_code = 245
	-15      ,           //degrees C adc_code = 246
	-15      ,           //degrees C adc_code = 247
	-14      ,           //degrees C adc_code = 248
	-13      ,           //degrees C adc_code = 249
	-12      ,           //degrees C adc_code = 250
	-11      ,           //degrees C adc_code = 251
	-11      ,           //degrees C adc_code = 252
	-10      ,           //degrees C adc_code = 253
	-9        ,           //degrees C adc_code = 254
	-8        ,           //degrees C adc_code = 255
	-8        ,           //degrees C adc_code = 256
	-7        ,           //degrees C adc_code = 257
	-6        ,           //degrees C adc_code = 258
	-5        ,           //degrees C adc_code = 259
	-5        ,           //degrees C adc_code = 260
	-4        ,           //degrees C adc_code = 261
	-3        ,           //degrees C adc_code = 262
	-2        ,           //degrees C adc_code = 263
	-2        ,           //degrees C adc_code = 264
	-1        ,           //degrees C adc_code = 265
	0          ,           //degrees C adc_code = 266
	1          ,           //degrees C adc_code = 267
	1          ,           //degrees C adc_code = 268
	2          ,           //degrees C adc_code = 269
	3          ,           //degrees C adc_code = 270
	4          ,           //degrees C adc_code = 271
	4          ,           //degrees C adc_code = 272
	5          ,           //degrees C adc_code = 273
	6          ,           //degrees C adc_code = 274
	7          ,           //degrees C adc_code = 275
	7          ,           //degrees C adc_code = 276
	8          ,           //degrees C adc_code = 277
	9          ,           //degrees C adc_code = 278
	10        ,           //degrees C adc_code = 279
	10        ,           //degrees C adc_code = 280
	11        ,           //degrees C adc_code = 281
	12        ,           //degrees C adc_code = 282
	12        ,           //degrees C adc_code = 283
	13        ,           //degrees C adc_code = 284
	14        ,           //degrees C adc_code = 285
	14        ,           //degrees C adc_code = 286
	15        ,           //degrees C adc_code = 287
	16        ,           //degrees C adc_code = 288
	17        ,           //degrees C adc_code = 289
	17        ,           //degrees C adc_code = 290
	18        ,           //degrees C adc_code = 291
	19        ,           //degrees C adc_code = 292
	20        ,           //degrees C adc_code = 293
	20        ,           //degrees C adc_code = 294
	21        ,           //degrees C adc_code = 295
	21        ,           //degrees C adc_code = 296
	22        ,           //degrees C adc_code = 297
	23        ,           //degrees C adc_code = 298
	24        ,           //degrees C adc_code = 299
	25        ,           //degrees C adc_code = 300
	25        ,           //degrees C adc_code = 301
	26        ,           //degrees C adc_code = 302
	27        ,           //degrees C adc_code = 303
	27        ,           //degrees C adc_code = 304
	28        ,           //degrees C adc_code = 305
	29        ,           //degrees C adc_code = 306
	29        ,           //degrees C adc_code = 307
	30        ,           //degrees C adc_code = 308
	31        ,           //degrees C adc_code = 309
	31        ,           //degrees C adc_code = 310
	32        ,           //degrees C adc_code = 311
	33        ,           //degrees C adc_code = 312
	34        ,           //degrees C adc_code = 313
	34        ,           //degrees C adc_code = 314
	35        ,           //degrees C adc_code = 315
	36        ,           //degrees C adc_code = 316
	36        ,           //degrees C adc_code = 317
	37        ,           //degrees C adc_code = 318
	38        ,           //degrees C adc_code = 319
	38        ,           //degrees C adc_code = 320
	39        ,           //degrees C adc_code = 321
	40        ,           //degrees C adc_code = 322
	40        ,           //degrees C adc_code = 323
	41        ,           //degrees C adc_code = 324
	42        ,           //degrees C adc_code = 325
	42        ,           //degrees C adc_code = 326
	43        ,           //degrees C adc_code = 327
	44        ,           //degrees C adc_code = 328
	44        ,           //degrees C adc_code = 329
	45        ,           //degrees C adc_code = 330
	46        ,           //degrees C adc_code = 331
	46        ,           //degrees C adc_code = 332
	47        ,           //degrees C adc_code = 333
	47        ,           //degrees C adc_code = 334
	48        ,           //degrees C adc_code = 335
	48        ,           //degrees C adc_code = 336
	49        ,           //degrees C adc_code = 337
	50        ,           //degrees C adc_code = 338
	51        ,           //degrees C adc_code = 339
	52        ,           //degrees C adc_code = 340
	52        ,           //degrees C adc_code = 341
	53        ,           //degrees C adc_code = 342
	54        ,           //degrees C adc_code = 343
	54        ,           //degrees C adc_code = 344
	55        ,           //degrees C adc_code = 345
	56        ,           //degrees C adc_code = 346
	56        ,           //degrees C adc_code = 347
	57        ,           //degrees C adc_code = 348
	58        ,           //degrees C adc_code = 349
	58        ,           //degrees C adc_code = 350
	59        ,           //degrees C adc_code = 351
	59        ,           //degrees C adc_code = 352
	60        ,           //degrees C adc_code = 353
	61        ,           //degrees C adc_code = 354
	61        ,           //degrees C adc_code = 355
	62        ,           //degrees C adc_code = 356
	63        ,           //degrees C adc_code = 357
	64        ,           //degrees C adc_code = 358
	64        ,           //degrees C adc_code = 359
	65        ,           //degrees C adc_code = 360
	65        ,           //degrees C adc_code = 361
	66        ,           //degrees C adc_code = 362
	67        ,           //degrees C adc_code = 363
	67        ,           //degrees C adc_code = 364
	68        ,           //degrees C adc_code = 365
	69        ,           //degrees C adc_code = 366
	69        ,           //degrees C adc_code = 367
	70        ,           //degrees C adc_code = 368
	70        ,           //degrees C adc_code = 369
	71        ,           //degrees C adc_code = 370
	72        ,           //degrees C adc_code = 371
	72        ,           //degrees C adc_code = 372
	73        ,           //degrees C adc_code = 373
	73        ,           //degrees C adc_code = 374
	74        ,           //degrees C adc_code = 375
	74        ,           //degrees C adc_code = 376
	75        ,           //degrees C adc_code = 377
	75        ,           //degrees C adc_code = 378
	76        ,           //degrees C adc_code = 379
	77        ,           //degrees C adc_code = 380
	78        ,           //degrees C adc_code = 381
	79        ,           //degrees C adc_code = 382
	79        ,           //degrees C adc_code = 383
	80        ,           //degrees C adc_code = 384
	81        ,           //degrees C adc_code = 385
	81        ,           //degrees C adc_code = 386
	82        ,           //degrees C adc_code = 387
	82        ,           //degrees C adc_code = 388
	83        ,           //degrees C adc_code = 389
	84        ,           //degrees C adc_code = 390
	84        ,           //degrees C adc_code = 391
	85        ,           //degrees C adc_code = 392
	86        ,           //degrees C adc_code = 393
	86        ,           //degrees C adc_code = 394
	87        ,           //degrees C adc_code = 395
	87        ,           //degrees C adc_code = 396
	87        ,           //degrees C adc_code = 397
	88        ,           //degrees C adc_code = 398
	89        ,           //degrees C adc_code = 399
	89        ,           //degrees C adc_code = 400
	90        ,           //degrees C adc_code = 401
	91        ,           //degrees C adc_code = 402
	92        ,           //degrees C adc_code = 403
	92        ,           //degrees C adc_code = 404
	93        ,           //degrees C adc_code = 405
	94        ,           //degrees C adc_code = 406
	94        ,           //degrees C adc_code = 407
	95        ,           //degrees C adc_code = 408
	95        ,           //degrees C adc_code = 409
	96        ,           //degrees C adc_code = 410
	97        ,           //degrees C adc_code = 411
	98        ,           //degrees C adc_code = 412
	99        ,           //degrees C adc_code = 413
	100       ,           //degrees C adc_code = 414
	100       ,           //degrees C adc_code = 415
	100      ,           //degrees C adc_code = 416
	100      ,           //degrees C adc_code = 417
	101      ,           //degrees C adc_code = 418
	102      ,           //degrees C adc_code = 419
	102      ,           //degrees C adc_code = 420
	103      ,           //degrees C adc_code = 421
	103      ,           //degrees C adc_code = 422
	104      ,           //degrees C adc_code = 423
	105      ,           //degrees C adc_code = 424
	105      ,           //degrees C adc_code = 425
	106      ,           //degrees C adc_code = 426
	106      ,           //degrees C adc_code = 427
	107      ,           //degrees C adc_code = 428
	108      ,           //degrees C adc_code = 429
	108      ,           //degrees C adc_code = 430
	109      ,           //degrees C adc_code = 431
	109      ,           //degrees C adc_code = 432
	110      ,           //degrees C adc_code = 433
	111      ,           //degrees C adc_code = 434
	112      ,           //degrees C adc_code = 435
	112      ,           //degrees C adc_code = 436
	113      ,           //degrees C adc_code = 437
	113      ,           //degrees C adc_code = 438
	114      ,           //degrees C adc_code = 439
	114      ,           //degrees C adc_code = 440
	115      ,           //degrees C adc_code = 441
	115      ,           //degrees C adc_code = 442
	116      ,           //degrees C adc_code = 443
	116      ,           //degrees C adc_code = 444
	117      ,           //degrees C adc_code = 445
	118      ,           //degrees C adc_code = 446
	118      ,           //degrees C adc_code = 447
	119      ,           //degrees C adc_code = 448
	120      ,           //degrees C adc_code = 449
	120      ,           //degrees C adc_code = 450
	121      ,           //degrees C adc_code = 451
	122      ,           //degrees C adc_code = 452
	122      ,           //degrees C adc_code = 453
	123      ,           //degrees C adc_code = 454
	123      ,           //degrees C adc_code = 455
	124      ,           //degrees C adc_code = 456
	125      ,           //degrees C adc_code = 457
	125      ,           //degrees C adc_code = 458
	126      ,           //degrees C adc_code = 459
	126      ,           //degrees C adc_code = 460
	127      ,           //degrees C adc_code = 461
	127      ,           //degrees C adc_code = 462
	128      ,           //degrees C adc_code = 463
	129      ,           //degrees C adc_code = 464
	129      ,           //degrees C adc_code = 465
	130      ,           //degrees C adc_code = 466
	130      ,           //degrees C adc_code = 467
	131      ,           //degrees C adc_code = 468
	132      ,           //degrees C adc_code = 469
	132      ,           //degrees C adc_code = 470
	133      ,           //degrees C adc_code = 471
	134      ,           //degrees C adc_code = 472
	134      ,           //degrees C adc_code = 473
	135      ,           //degrees C adc_code = 474
	135      ,           //degrees C adc_code = 475
	136      ,           //degrees C adc_code = 476
	136      ,           //degrees C adc_code = 477
	137      ,           //degrees C adc_code = 478
	137      ,           //degrees C adc_code = 479
	138      ,           //degrees C adc_code = 480
	138      ,           //degrees C adc_code = 481
	139      ,           //degrees C adc_code = 482
	140      ,           //degrees C adc_code = 483
	140      ,           //degrees C adc_code = 484
	141      ,           //degrees C adc_code = 485
	142      ,           //degrees C adc_code = 486
	143      ,           //degrees C adc_code = 487
	143      ,           //degrees C adc_code = 488
	143      ,           //degrees C adc_code = 489
	144      ,           //degrees C adc_code = 490
	145      ,           //degrees C adc_code = 491
	145      ,           //degrees C adc_code = 492
	146      ,           //degrees C adc_code = 493
	147      ,           //degrees C adc_code = 494
	148      ,           //degrees C adc_code = 495
	148      ,           //degrees C adc_code = 496
	148      ,           //degrees C adc_code = 497
	149      ,           //degrees C adc_code = 498
	149      ,           //degrees C adc_code = 499
	149      ,           //degrees C adc_code = 500
	149      ,           //degrees C adc_code = 501
	149      ,           //degrees C adc_code = 502
	150      ,           //degrees C adc_code = 503
	150      ,           //degrees C adc_code = 504
	150      ,           //degrees C adc_code = 505
	150      ,           //degrees C adc_code = 506
	150      ,           //degrees C adc_code = 507
	150      ,           //degrees C adc_code = 508
	150      ,           //degrees C adc_code = 509
	150      ,           //degrees C adc_code = 510
	150                  //degrees C adc_code = 511
};





#endif /* USER_PTC_TEMPERATURE_LUT_H_ */
