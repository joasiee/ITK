/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
/*
 * The definitions in this file were derived from genesis.tcl from
 * David Clunies Dicom3Tools
 *
 *
 * Copyright (c) 1993-2006, David A. Clunie DBA PixelMed Publishing. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimers.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimers in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of PixelMed Publishing nor the names of its contributors may
 *    be used to endorse or promote products derived from this software.
 *
 * This software is provided by the copyright holders and contributors "as is" and any
 * express or implied warranties, including, but not limited to, the implied warranties
 * of merchantability and fitness for a particular purpose are disclaimed. In no event
 * shall the copyright owner or contributors be liable for any direct, indirect, incidental,
 * special, exemplary, or consequential damages (including, but not limited to, procurement
 * of substitute goods or services; loss of use, data or profits; or business interruption)
 * however caused and on any theory of liability, whether in contract, strict liability, or
 * tort (including negligence or otherwise) arising in any way out of the use of this software,
 * even if advised of the possibility of such damage.
 *
 * This software has neither been tested nor approved for clinical use or for incorporation in
 * a medical device. It is the redistributor's or user's responsibility to comply with any
 * applicable local, state, national or international regulations.
 *
 */

#ifndef Ge5xHdr_h
#define Ge5xHdr_h
#include "ITKIOGEExport.h"

#define GE_5X_MAGIC_NUMBER 0x494d4746

struct Ge5xPixelHeader
{
  int            GENESIS_IH_img_magic;
  int            GENESIS_IH_img_hdr_length;
  int            GENESIS_IH_img_width;
  int            GENESIS_IH_img_height;
  int            GENESIS_IH_img_depth;
  int            GENESIS_IH_img_compress;
  int            GENESIS_IH_img_dwindow;
  int            GENESIS_IH_img_dlevel;
  int            GENESIS_IH_img_bgshade;
  int            GENESIS_IH_img_ovrflow;
  int            GENESIS_IH_img_undflow;
  int            GENESIS_IH_img_top_offset;
  int            GENESIS_IH_img_bot_offset;
  short          GENESIS_IH_img_version;
  unsigned short GENESIS_IH_img_checksum;
  int            GENESIS_IH_img_p_id;
  int            GENESIS_IH_img_l_id;
  int            GENESIS_IH_img_p_unpack;
  int            GENESIS_IH_img_l_unpack;
  int            GENESIS_IH_img_p_compress;
  int            GENESIS_IH_img_l_compress;
  int            GENESIS_IH_img_p_histo;
  int            GENESIS_IH_img_l_histo;
  int            GENESIS_IH_img_p_text;
  int            GENESIS_IH_img_l_text;
  int            GENESIS_IH_img_p_graphics;
  int            GENESIS_IH_img_l_graphics;
  int            GENESIS_IH_img_p_dbHdr;
  int            GENESIS_IH_img_l_dbHdr;
  int            GENESIS_IH_img_levelOffset;
  int            GENESIS_IH_img_p_user;
  int            GENESIS_IH_img_l_user;
  int            GENESIS_IH_img_p_suite;
  int            GENESIS_IH_img_l_suite;
  int            GENESIS_IH_img_p_exam;
  int            GENESIS_IH_img_l_exam;
  int            GENESIS_IH_img_p_series;
  int            GENESIS_IH_img_l_series;
  int            GENESIS_IH_img_p_image;
  int            GENESIS_IH_img_l_image;
};


enum GE_SUITE_HDR_ENUM
{
  GENESIS_SU_ID = 0,        /*  Suite ID */
  GENESIS_SU_UNIQ = 4,      /*  Make Unique Flag */
  GENESIS_SU_DISKID = 6,    /*  Disk ID */
  GENESIS_SU_PRODID = 7,    /*  Product ID */
  GENESIS_SU_VERSCRE = 20,  /*  Original Version of Record */
  GENESIS_SU_VERSCUR = 22,  /*  Current Version of Record */
  GENESIS_SU_CHECKSUM = 24, /*  Suite Record Checksum */
  GENESIS_SU_PADDING = 28,  /*  Spare Space */
  GENESIS_SU_HDR_LEN = 114  /*  Length of Suite Header */
};

enum GE_EXAM_HDR_ENUM
{
  GENESIS_EX_SUID = 0,       /* Suite Id for this Exam */
  GENESIS_EX_UNIQ = 4,       /* Make-Unique Flag */
  GENESIS_EX_DISKID = 6,     /* Disk ID for this Exam */
  GENESIS_EX_NO = 8,         /* Exam Number */
  GENESIS_EX_HOSPNAME = 10,  /* Hospital Name */
  GENESIS_EX_DETECT = 44,    /* Detector Type */
  GENESIS_EX_NUMCELLS = 46,  /* Number of cells in det */
  GENESIS_EX_ZEROCELL = 50,  /* Cell number at theta */
  GENESIS_EX_CELLSPACE = 54, /* Cell spacing */
  GENESIS_EX_SRCTODET = 58,
  GENESIS_EX_SRCTOISO = 62,
  GENESIS_EX_TUBETYP = 66,
  GENESIS_EX_DASTYP = 68,
  GENESIS_EX_NUM_DCNK = 70,
  GENESIS_EX_DCN_LEN = 72,
  GENESIS_EX_DCN_DENSITY = 76,
  GENESIS_EX_DCN_SHIFTCNT = 78,
  GENESIS_EX_MAGSTRENGTH = 80, /* Magnetic Strength Gauss*/
  GENESIS_EX_PATID = 84,       /* Patient ID for this Exam*/
  GENESIS_EX_PATNAME = 97,     /* Patient Name*/
  GENESIS_EX_PATAGE = 122,     /* Patient Age */
  GENESIS_EX_PATIAN = 124,     /* Patient Age Notation */
  GENESIS_EX_PATSEX = 126,
  GENESIS_EX_PATWEIGHT = 128, /* Patient Weight */
  GENESIS_EX_TRAUMA = 132,
  GENESIS_EX_HIST = 134,
  GENESIS_EX_REQNUM = 195,
  GENESIS_EX_EX_DATETIME = 208,
  GENESIS_EX_REFPHY = 212,
  GENESIS_EX_DIAGRAD = 245,
  GENESIS_EX_OP = 278,
  GENESIS_EX_DESC = 282,
  GENESIS_EX_TYP = 305,
  GENESIS_EX_FORMAT = 308,
  GENESIS_EX_FIRSTAXTIME = 310,
  GENESIS_EX_SYSID = 318,
  GENESIS_EX_LASTMOD = 328,
  GENESIS_EX_PROTOCOLFLAG = 332,
  GENESIS_EX_ALLOC_KEY = 334,
  GENESIS_EX_DELTA_CNT = 348,
  GENESIS_EX_VERSCRE = 352,
  GENESIS_EX_VERSCUR = 354,
  GENESIS_EX_CHECKSUM = 356,
  GENESIS_EX_COMPLETE = 360,
  GENESIS_EX_SERIESCT = 364,
  GENESIS_EX_NUMARCH = 368,
  GENESIS_EX_NUMSERIES = 372,
  GENESIS_EX_NUMUNSER = 384,
  GENESIS_EX_TOARCHCNT = 396,
  GENESIS_EX_PROSPCNT = 408,
  GENESIS_EX_MODELNUM = 420,
  GENESIS_EX_MODELCNT = 424,
  GENESIS_EX_STAT = 436,
  GENESIS_EX_UNIQ_SYS_ID = 438,
  GENESIS_EX_SERVICE_ID = 454,
  GENESIS_EX_MOBILE_LOC = 470,
  GENESIS_EX_STUDY_UID = 474,
  GENESIS_EX_PADDING = 506,
  GENESIS_EX_HDR_LEN = 1024
};

enum GE_5X_SEHDR_ENUM
{
  GENESIS_SE_SUID = 0,
  GENESIS_SE_UNIQ = 4,
  GENESIS_SE_DISKID = 6,
  GENESIS_SE_EXNO = 8,
  GENESIS_SE_NO = 10,
  GENESIS_SE_DATETIME = 12,
  GENESIS_SE_ACTUAL_DT = 16,
  GENESIS_SE_DESC = 20,
  GENESIS_SE_PR_SYSID = 50,
  GENESIS_SE_PANSYSID = 59,
  GENESIS_SE_TYP = 68,
  GENESIS_SE_SOURCE = 70,
  GENESIS_SE_PLANE = 72,
  GENESIS_SE_SCAN_TYPE = 74,
  GENESIS_SE_POSITION = 76,
  GENESIS_SE_ENTRY = 80,
  GENESIS_SE_ANREF = 84,
  GENESIS_SE_LMHOR = 88,
  GENESIS_SE_PRTCL = 92,
  GENESIS_SE_CONTRAST = 118,
  GENESIS_SE_START_RAS = 120,
  GENESIS_SE_START_LOC = 122,
  GENESIS_SE_END_RAS = 126,
  GENESIS_SE_END_LOC = 128,
  GENESIS_SE_SE_PSEQ = 132,
  GENESIS_SE_SORTORDER = 134,
  GENESIS_SE_LNDMRKCNT = 136,
  GENESIS_SE_NACQ = 140,
  GENESIS_SE_XBASEST = 142,
  GENESIS_SE_XBASEEND = 144,
  GENESIS_SE_XENHST = 146,
  GENESIS_SE_XENHEND = 148,
  GENESIS_SE_LASTMOD = 150,
  GENESIS_SE_ALLOC_KEY = 154,
  GENESIS_SE_DELTA_CNT = 168,
  GENESIS_SE_VERSCRE = 172,
  GENESIS_SE_VERSCUR = 174,
  GENESIS_SE_PDS_A = 176,
  GENESIS_SE_PDS_C = 180,
  GENESIS_SE_PDS_U = 184,
  GENESIS_SE_CHECKSUM = 188,
  GENESIS_SE_COMPLETE = 192,
  GENESIS_SE_NUMARCH = 196,
  GENESIS_SE_IMAGECT = 200,
  GENESIS_SE_NUMIMAGES = 204,
  GENESIS_SE_NUMUNIMG = 216,
  GENESIS_SE_TOARCHCNT = 228,
  GENESIS_SE_ECHO1_ALPHA = 240,
  GENESIS_SE_ECHO1_BETA = 244,
  GENESIS_SE_ECHO1_WINDOW = 248,
  GENESIS_SE_ECHO1_LEVEL = 250,
  GENESIS_SE_ECHO2_ALPHA = 252,
  GENESIS_SE_ECHO2_BETA = 256,
  GENESIS_SE_ECHO2_WINDOW = 260,
  GENESIS_SE_ECHO2_LEVEL = 262,
  GENESIS_SE_ECHO3_ALPHA = 264,
  GENESIS_SE_ECHO3_BETA = 268,
  GENESIS_SE_ECHO3_WINDOW = 272,
  GENESIS_SE_ECHO3_LEVEL = 274,
  GENESIS_SE_ECHO4_ALPHA = 276,
  GENESIS_SE_ECHO4_BETA = 280,
  GENESIS_SE_ECHO4_WINDOW = 284,
  GENESIS_SE_ECHO4_LEVEL = 286,
  GENESIS_SE_ECHO5_ALPHA = 288,
  GENESIS_SE_ECHO5_BETA = 292,
  GENESIS_SE_ECHO5_WINDOW = 296,
  GENESIS_SE_ECHO5_LEVEL = 298,
  GENESIS_SE_ECHO6_ALPHA = 300,
  GENESIS_SE_ECHO6_BETA = 304,
  GENESIS_SE_ECHO6_WINDOW = 308,
  GENESIS_SE_ECHO6_LEVEL = 310,
  GENESIS_SE_ECHO7_ALPHA = 312,
  GENESIS_SE_ECHO7_BETA = 316,
  GENESIS_SE_ECHO7_WINDOW = 320,
  GENESIS_SE_ECHO7_LEVEL = 322,
  GENESIS_SE_ECHO8_ALPHA = 324,
  GENESIS_SE_ECHO8_BETA = 328,
  GENESIS_SE_ECHO8_WINDOW = 332,
  GENESIS_SE_ECHO8_LEVEL = 334,
  GENESIS_SE_SERIES_UID = 336,
  GENESIS_SE_LANDMARK_UID = 368,
  GENESIS_SE_EQUIPMENT_UID = 400,
  GENESIS_SE_PADDING = 432,
  GENESIS_SE_HDR_LEN = 1020
};

enum GE_5X_CTHDR_ENUM
{
  GENESIS_CT_IM_SUID = 0,
  GENESIS_CT_IM_UNIQ = 4,
  GENESIS_CT_IM_DISKID = 6,
  GENESIS_CT_IM_EXNO = 8,
  GENESIS_CT_IM_SENO = 10,
  GENESIS_CT_IM_NO = 12,
  GENESIS_CT_IM_DATETIME = 14,
  GENESIS_CT_IM_ACTUAL_DT = 18,
  GENESIS_CT_SCTIME = 22,
  GENESIS_CT_SLTHICK = 26,
  GENESIS_CT_IMATRIX_X = 30,
  GENESIS_CT_IMATRIX_Y = 32,
  GENESIS_CT_DFOV = 34,
  GENESIS_CT_DFOV_RECT = 38,
  GENESIS_CT_DIM_X = 42,
  GENESIS_CT_DIM_Y = 46,
  GENESIS_CT_PIXSIZE_X = 50,
  GENESIS_CT_PIXSIZE_Y = 54,
  GENESIS_CT_PDID = 58,
  GENESIS_CT_CONTRASTIV = 72,
  GENESIS_CT_CONTRASTORAL = 89,
  GENESIS_CT_CONTMODE = 106,
  GENESIS_CT_SERRX = 108,
  GENESIS_CT_IMGRX = 110,
  GENESIS_CT_SCREENFORMAT = 112,
  GENESIS_CT_PLANE = 114,
  GENESIS_CT_SCANSPACING = 116,
  GENESIS_CT_IM_COMPRESS = 120,
  GENESIS_CT_IM_SCOUTTYPE = 122,
  GENESIS_CT_LOC_RAS = 124,
  GENESIS_CT_LOC = 126,
  GENESIS_CT_CTR_R = 130,
  GENESIS_CT_CTR_A = 134,
  GENESIS_CT_CTR_S = 138,
  GENESIS_CT_NORM_R = 142,
  GENESIS_CT_NORM_A = 146,
  GENESIS_CT_NORM_S = 150,
  GENESIS_CT_TLHC_R = 154,
  GENESIS_CT_TLHC_A = 158,
  GENESIS_CT_TLHC_S = 162,
  GENESIS_CT_TRHC_R = 166,
  GENESIS_CT_TRHC_A = 170,
  GENESIS_CT_TRHC_S = 174,
  GENESIS_CT_BRHC_R = 178,
  GENESIS_CT_BRHC_A = 182,
  GENESIS_CT_BRHC_S = 186,
  GENESIS_CT_FORIMGREV = 190,
  GENESIS_CT_SCTSTR = 194,
  GENESIS_CT_SCTEND = 198,
  GENESIS_CT_TBLSPD = 202,
  GENESIS_CT_TBLHT = 206,
  GENESIS_CT_MIDSTIME = 210,
  GENESIS_CT_MIDSFLAG = 214,
  GENESIS_CT_KVOLT = 216,
  GENESIS_CT_MAMP = 220,
  GENESIS_CT_GANTILT = 224,
  GENESIS_CT_AZIMUTH = 228,
  GENESIS_CT_GANVEL = 232,
  GENESIS_CT_GANFILT = 236,
  GENESIS_CT_TRIGON = 240,
  GENESIS_CT_DEGROT = 244,
  GENESIS_CT_XRAYON = 248,
  GENESIS_CT_XRAYOFF = 252,
  GENESIS_CT_NUMTRIG = 256,
  GENESIS_CT_INVIEWS = 260,
  GENESIS_CT_VIEW1ANG = 262,
  GENESIS_CT_TRIGFREQ = 266,
  GENESIS_CT_TRIGSRC = 270,
  GENESIS_CT_FPAGAIN = 274,
  GENESIS_CT_SCANOPMODE = 278,
  GENESIS_CT_OUTSRC = 282,
  GENESIS_CT_ADIN = 286,
  GENESIS_CT_CALMODE = 290,
  GENESIS_CT_CALFREQ = 294,
  GENESIS_CT_REGXM = 298,
  GENESIS_CT_AUTOZERO = 302,
  GENESIS_CT_SFOVTYP = 306,
  GENESIS_CT_PHANTSIZE = 308,
  GENESIS_CT_PHANTTYP = 310,
  GENESIS_CT_FILTTYP = 312,
  GENESIS_CT_RECONALG = 314,
  GENESIS_CT_PERISFLAG = 316,
  GENESIS_CT_IBONEFLAG = 318,
  GENESIS_CT_STATFLAG = 320,
  GENESIS_CT_COMPUTETYP = 322,
  GENESIS_CT_SEGNUM = 324,
  GENESIS_CT_SEGSTOTAL = 326,
  GENESIS_CT_ISD = 328,
  GENESIS_CT_SFOVMM = 332,
  GENESIS_CT_SCANNUM = 336,
  GENESIS_CT_VIEWSTRTCHAN = 338,
  GENESIS_CT_VIEWCOMPFCTR = 340,
  GENESIS_CT_OUTVIEWS = 342,
  GENESIS_CT_OVERRANGES = 344,
  GENESIS_CT_TOTREFCHAN = 346,
  GENESIS_CT_SCDATASIZE = 348,
  GENESIS_CT_REFCHAN1 = 352,
  GENESIS_CT_REFCHAN2 = 354,
  GENESIS_CT_REFCHAN3 = 356,
  GENESIS_CT_REFCHAN4 = 358,
  GENESIS_CT_REFCHAN5 = 360,
  GENESIS_CT_REFCHAN6 = 362,
  GENESIS_CT_POSTPROC = 364,
  GENESIS_CT_XMPAT = 366,
  GENESIS_CT_ROTTYP = 370,
  GENESIS_CT_RAWDATAFLAG = 372,
  GENESIS_CT_CT_SCALEFACT = 374,
  GENESIS_CT_CT_WATER_NUM = 378,
  GENESIS_CT_CT_BONE_NUM = 380,
  GENESIS_CT_BBH_COEF1 = 382,
  GENESIS_CT_BBH_COEF2 = 386,
  GENESIS_CT_BBH_COEF3 = 390,
  GENESIS_CT_BBH_NUMBLEND = 394,
  GENESIS_CT_FIRSTCHAN = 396,
  GENESIS_CT_NUMCHAN = 400,
  GENESIS_CT_CHANINC = 404,
  GENESIS_CT_FIRSTVIEW = 408,
  GENESIS_CT_NUMVIEW = 412,
  GENESIS_CT_VIEWINC = 416,
  GENESIS_CT_WINDOWRANGE = 420,
  GENESIS_CT_SCALEMIN = 424,
  GENESIS_CT_SCALEMAX = 428,
  GENESIS_CT_DATAMOD = 432,
  GENESIS_CT_QCALFILE = 436,
  GENESIS_CT_CALMODFILE = 449,
  GENESIS_CT_WORDSPERVIEW = 462,
  GENESIS_CT_RL_RAS = 464,
  GENESIS_CT_AP_RAS = 465,
  GENESIS_CT_SCTSTR_RAS = 466,
  GENESIS_CT_SCTEND_RAS = 467,
  GENESIS_CT_SCT_ANREF = 468,
  GENESIS_CT_PPS_SCALWIN = 472,
  GENESIS_CT_PPS_QCALFLAG = 474,
  GENESIS_CT_PPS_PCALFLAG = 476,
  GENESIS_CT_PPS_THETAFIX = 478,
  GENESIS_CT_PPS_BHFLAG = 480,
  GENESIS_CT_SPOT_SIZE = 482,
  GENESIS_CT_SPOT_POS = 484,
  GENESIS_CT_RECONDATASET = 486,
  GENESIS_CT_NDETCELLSFOV = 488,
  GENESIS_CT_STRTSCANTIME = 490,
  GENESIS_CT_GANDIR = 498,
  GENESIS_CT_ROTORSPEED = 500,
  GENESIS_CT_TRIGMODE = 502,
  GENESIS_CT_SITILT = 504,
  GENESIS_CT_TARGCEN_R = 508,
  GENESIS_CT_TARGCEN_A = 512,
  GENESIS_CT_BACKPROJFLAG = 516,
  GENESIS_CT_FATQESTFLAG = 518,
  GENESIS_CT_ZAVG = 520,
  GENESIS_CT_LEFTREFAVG = 524,
  GENESIS_CT_LEFTREFMAX = 528,
  GENESIS_CT_RIGHTREFAVG = 532,
  GENESIS_CT_RIGHTREFMAX = 536,
  GENESIS_CT_IM_ALLOC_KEY = 540,
  GENESIS_CT_IM_LASTMOD = 554,
  GENESIS_CT_IM_VERSCRE = 558,
  GENESIS_CT_IM_VERSCUR = 560,
  GENESIS_CT_IM_PDS_A = 562,
  GENESIS_CT_IM_PDS_C = 566,
  GENESIS_CT_IM_PDS_U = 570,
  GENESIS_CT_IM_CHECKSUM = 574,
  GENESIS_CT_IM_ARCHIVED = 578,
  GENESIS_CT_IM_COMPLETE = 582,
  GENESIS_CT_BIOP_POS = 586,
  GENESIS_CT_BIOP_TLOC = 588,
  GENESIS_CT_BIOP_REFLOC = 592,
  GENESIS_CT_REF_CHAN = 596,
  GENESIS_CT_BP_COEF = 598,
  GENESIS_CT_PSC = 602,
  GENESIS_CT_OVERRNG_CORR = 604,
  GENESIS_CT_DYN_Z_ALPHA = 606,
  GENESIS_CT_REF_IMG = 610,
  GENESIS_CT_SUM_IMG = 611,
  GENESIS_CT_IMG_WINDOW = 612,
  GENESIS_CT_IMG_LEVEL = 614,
  GENESIS_CT_SLOP_INT_1 = 616,
  GENESIS_CT_SLOP_INT_2 = 620,
  GENESIS_CT_SLOP_INT_3 = 624,
  GENESIS_CT_SLOP_INT_4 = 628,
  GENESIS_CT_SLOP_INT_5 = 632,
  GENESIS_CT_SLOP_FLOAT_1 = 636,
  GENESIS_CT_SLOP_FLOAT_2 = 640,
  GENESIS_CT_SLOP_FLOAT_3 = 644,
  GENESIS_CT_SLOP_FLOAT_4 = 648,
  GENESIS_CT_SLOP_FLOAT_5 = 652,
  GENESIS_CT_SLOP_STR_1 = 656,
  GENESIS_CT_SLOP_STR_2 = 672,
  GENESIS_CT_DELTASTART = 688,
  GENESIS_CT_MAXOVERRANGE = 692,
  GENESIS_CT_AVGOVERRANGE = 696,
  GENESIS_CT_AFTERGLOW = 700,
  GENESIS_CT_Z_BLOCKED = 702,
  GENESIS_CT_REF1_BLOCKED = 704,
  GENESIS_CT_REF2_BLOCKED = 706,
  GENESIS_CT_REF3_BLOCKED = 708,
  GENESIS_CT_REF4_BLOCKED = 710,
  GENESIS_CT_REF5_BLOCKED = 712,
  GENESIS_CT_INTEGRITY = 714,
  GENESIS_CT_PITCHRATIO = 716,
  GENESIS_CT_IMAGE_UID = 724,
  GENESIS_CT_SOP_UID = 756,
  GENESIS_CT_XRAYDELAY = 788,
  GENESIS_CT_XRAYDURATION = 792,
  GENESIS_CT_PADDING = 796
};

enum GE_5X_MRHDR_ENUM
{
  GENESIS_MR_IM_SUID = 0,
  GENESIS_MR_IM_UNIQ = 4,
  GENESIS_MR_IM_DISKID = 6,
  GENESIS_MR_IM_EXNO = 8,
  GENESIS_MR_IM_SENO = 10,
  GENESIS_MR_IM_NO = 12,
  GENESIS_MR_IM_DATETIME = 14,
  GENESIS_MR_IM_ACTUAL_DT = 18,
  GENESIS_MR_SCTIME = 22,
  GENESIS_MR_SLTHICK = 26,
  GENESIS_MR_IMATRIX_X = 30,
  GENESIS_MR_IMATRIX_Y = 32,
  GENESIS_MR_DFOV = 34,
  GENESIS_MR_DFOV_RECT = 38,
  GENESIS_MR_DIM_X = 42,
  GENESIS_MR_DIM_Y = 46,
  GENESIS_MR_PIXSIZE_X = 50,
  GENESIS_MR_PIXSIZE_Y = 54,
  GENESIS_MR_PDID = 58,
  GENESIS_MR_CONTRASTIV = 72,
  GENESIS_MR_CONTRASTORAL = 89,
  GENESIS_MR_CONTMODE = 106,
  GENESIS_MR_SERRX = 108,
  GENESIS_MR_IMGRX = 110,
  GENESIS_MR_SCREENFORMAT = 112,
  GENESIS_MR_PLANE = 114,
  GENESIS_MR_SCANSPACING = 116,
  GENESIS_MR_IM_COMPRESS = 120,
  GENESIS_MR_IM_SCOUTTYPE = 122,
  GENESIS_MR_LOC_RAS = 124,
  GENESIS_MR_LOC = 126,
  GENESIS_MR_CTR_R = 130,
  GENESIS_MR_CTR_A = 134,
  GENESIS_MR_CTR_S = 138,
  GENESIS_MR_NORM_R = 142,
  GENESIS_MR_NORM_A = 146,
  GENESIS_MR_NORM_S = 150,
  GENESIS_MR_TLHC_R = 154,
  GENESIS_MR_TLHC_A = 158,
  GENESIS_MR_TLHC_S = 162,
  GENESIS_MR_TRHC_R = 166,
  GENESIS_MR_TRHC_A = 170,
  GENESIS_MR_TRHC_S = 174,
  GENESIS_MR_BRHC_R = 178,
  GENESIS_MR_BRHC_A = 182,
  GENESIS_MR_BRHC_S = 186,
  GENESIS_MR_FORIMGREV = 190,
  GENESIS_MR_TR = 194,
  GENESIS_MR_TI = 198,
  GENESIS_MR_TE = 202,
  GENESIS_MR_TE2 = 206,
  GENESIS_MR_NUMECHO = 210,
  GENESIS_MR_ECHONUM = 212,
  GENESIS_MR_TBLDLTA = 214,
  GENESIS_MR_NEX = 218,
  GENESIS_MR_CONTIG = 222,
  GENESIS_MR_HRTRATE = 224,
  GENESIS_MR_TDEL = 226,
  GENESIS_MR_SARAVG = 230,
  GENESIS_MR_SARPEAK = 234,
  GENESIS_MR_MONSAR = 238,
  GENESIS_MR_TRGWINDOW = 240,
  GENESIS_MR_REPTIME = 242,
  GENESIS_MR_IMGPCYC = 246,
  GENESIS_MR_XMTGAIN = 248,
  GENESIS_MR_RCVGAIN1 = 250,
  GENESIS_MR_RCVGAIN2 = 252,
  GENESIS_MR_FLIP = 254,
  GENESIS_MR_MINDAT = 256,
  GENESIS_MR_CPHASE = 260,
  GENESIS_MR_SWAPPF = 262,
  GENESIS_MR_PAUSEINT = 264,
  GENESIS_MR_PAUSETIME = 266,
  GENESIS_MR_OBPLANE = 270,
  GENESIS_MR_SLOCFOV = 274,
  GENESIS_MR_XMTFREQ = 278,
  GENESIS_MR_AUTOXMTFREQ = 282,
  GENESIS_MR_AUTOXMTGAIN = 286,
  GENESIS_MR_PRESCAN_R1 = 288,
  GENESIS_MR_PRESCAN_R2 = 290,
  GENESIS_MR_USER_BITMAP = 292,
  GENESIS_MR_CENFREQ = 296,
  GENESIS_MR_IMODE = 298,
  GENESIS_MR_IOPT = 300,
  GENESIS_MR_PSEQ = 304,
  GENESIS_MR_PSEQMODE = 306,
  GENESIS_MR_PSDNAME = 308,
  GENESIS_MR_PSD_DATETIME = 342,
  GENESIS_MR_PSD_INAME = 346,
  GENESIS_MR_CTYP = 360,
  GENESIS_MR_CNAME = 362,
  GENESIS_MR_SURFCTYP = 380,
  GENESIS_MR_SURFCEXT = 382,
  GENESIS_MR_RAWRUNNUM = 384,
  GENESIS_MR_CAL_FLDSTR = 388,
  GENESIS_MR_SUPP_TECH = 392,
  GENESIS_MR_VBW = 394,
  GENESIS_MR_SLQUANT = 398,
  GENESIS_MR_GPRE = 400,
  GENESIS_MR_INTR_DEL = 402,
  GENESIS_MR_USER0 = 406,
  GENESIS_MR_USER1 = 410,
  GENESIS_MR_USER2 = 414,
  GENESIS_MR_USER3 = 418,
  GENESIS_MR_USER4 = 422,
  GENESIS_MR_USER5 = 426,
  GENESIS_MR_USER6 = 430,
  GENESIS_MR_USER7 = 434,
  GENESIS_MR_USER8 = 438,
  GENESIS_MR_USER9 = 442,
  GENESIS_MR_USER10 = 446,
  GENESIS_MR_USER11 = 450,
  GENESIS_MR_USER12 = 454,
  GENESIS_MR_USER13 = 458,
  GENESIS_MR_USER14 = 462,
  GENESIS_MR_USER15 = 466,
  GENESIS_MR_USER16 = 470,
  GENESIS_MR_USER17 = 474,
  GENESIS_MR_USER18 = 478,
  GENESIS_MR_USER19 = 482,
  GENESIS_MR_USER20 = 486,
  GENESIS_MR_USER21 = 490,
  GENESIS_MR_USER22 = 494,
  GENESIS_MR_USER23 = 498,
  GENESIS_MR_USER24 = 502,
  GENESIS_MR_IM_ALLOC_KEY = 506,
  GENESIS_MR_IM_LASTMOD = 520,
  GENESIS_MR_IM_VERSCRE = 524,
  GENESIS_MR_IM_VERSCUR = 526,
  GENESIS_MR_IM_PDS_A = 528,
  GENESIS_MR_IM_PDS_C = 532,
  GENESIS_MR_IM_PDS_U = 536,
  GENESIS_MR_IM_CHECKSUM = 540,
  GENESIS_MR_IM_ARCHIVED = 544,
  GENESIS_MR_IM_COMPLETE = 548,
  GENESIS_MR_SATBITS = 552,
  GENESIS_MR_SCIC = 554,
  GENESIS_MR_SATXLOC1 = 556,
  GENESIS_MR_SATXLOC2 = 558,
  GENESIS_MR_SATYLOC1 = 560,
  GENESIS_MR_SATYLOC2 = 562,
  GENESIS_MR_SATZLOC1 = 564,
  GENESIS_MR_SATZLOC2 = 566,
  GENESIS_MR_SATXTHICK = 568,
  GENESIS_MR_SATYTHICK = 570,
  GENESIS_MR_SATZTHICK = 572,
  GENESIS_MR_FLAX = 574,
  GENESIS_MR_VENC = 576,
  GENESIS_MR_THK_DISCLMR = 578,
  GENESIS_MR_PS_FLAG = 580,
  GENESIS_MR_PS_STATUS = 582,
  GENESIS_MR_IMAGE_TYPE = 584,
  GENESIS_MR_VAS_COLLAPSE = 586,
  GENESIS_MR_USER23N = 588,
  GENESIS_MR_USER24N = 592,
  GENESIS_MR_PROJ_ALG = 596,
  GENESIS_MR_PROJ_NAME = 598,
  GENESIS_MR_X_AXIS_ROT = 612,
  GENESIS_MR_Y_AXIS_ROT = 616,
  GENESIS_MR_Z_AXIS_ROT = 620,
  GENESIS_MR_THRESH_MIN1 = 624,
  GENESIS_MR_THRESH_MAX1 = 628,
  GENESIS_MR_THRESH_MIN2 = 632,
  GENESIS_MR_THRESH_MAX2 = 636,
  GENESIS_MR_ECHO_TRN_LEN = 640,
  GENESIS_MR_FRAC_ECHO = 642,
  GENESIS_MR_PREP_PULSE = 644,
  GENESIS_MR_CPHASENUM = 646,
  GENESIS_MR_VAR_ECHO = 648,
  GENESIS_MR_REF_IMG = 650,
  GENESIS_MR_SUM_IMG = 651,
  GENESIS_MR_IMG_WINDOW = 652,
  GENESIS_MR_IMG_LEVEL = 654,
  GENESIS_MR_SLOP_INT_1 = 656,
  GENESIS_MR_SLOP_INT_2 = 660,
  GENESIS_MR_SLOP_INT_3 = 664,
  GENESIS_MR_SLOP_INT_4 = 668,
  GENESIS_MR_SLOP_INT_5 = 672,
  GENESIS_MR_SLOP_FLOAT_1 = 676,
  GENESIS_MR_SLOP_FLOAT_2 = 680,
  GENESIS_MR_SLOP_FLOAT_3 = 684,
  GENESIS_MR_SLOP_FLOAT_4 = 688,
  GENESIS_MR_SLOP_FLOAT_5 = 692,
  GENESIS_MR_SLOP_STR_1 = 696,
  GENESIS_MR_SLOP_STR_2 = 712,
  GENESIS_MR_SCANACTNO = 728,
  GENESIS_MR_VASFLAGS = 730,
  GENESIS_MR_VENCSCALE = 732,
  GENESIS_MR_INTEGRITY = 736,
  GENESIS_MR_FPHASE = 738,
  GENESIS_MR_FREQ_DIR = 742,
  GENESIS_MR_VAS_MODE = 744,
  GENESIS_MR_IMAGE_UID = 746,
  GENESIS_MR_SOP_UID = 778,
  GENESIS_MR_PADDING = 810,
  GENESIS_MR_HDR_LEN = 1022
};


enum GE_5X_ON_OFF_ENUM
{
  GE_5X_OFF = 0,
  GE_5X_ON = 1
};

enum GE_5X_YES_NO_ENUM
{
  GE_5X_NO = 0,
  GE_5X_YES = 1
};

enum GE_5X_PREP_PULSE_ENUM
{
  GE_5X_PREP_NONE = 0, /* None */
  GE_5X_PREP_IR = 1,   /* Inversion Recovery*/
  GE_5X_PREP_DE = 2    /* Driven Equilibrium */
};

enum GE_5X_PROJECT_TYPE_ENUM
{
  GE_5X_PROJECT_NONE = 0,
  GE_5X_PROJECT_PROTO = 1,
  GE_5X_PROJECT_MIN = 2,
  GE_5X_PROJECT_MAX = 3
};

enum GE_5X_IMAGE_TYPE_ENUM
{
  GE_5X_IMAGE_MAG = 0,
  GE_5X_IMAGE_PHASE = 1,
  GE_5X_IMAGE_REAL = 2,
  GE_5X_IMAGE_IMAG = 3
};

enum GE_5X_VASCULAR_TYPE_ENUM
{
  GE_5X_COLLAPSE_NONE = 0,
  GE_5X_COLLAPSE_COL = 1,
  GE_5X_COLLAPSE_MAG = 2,
  GE_5X_COLLAPSE_RL = 3,
  GE_5X_COLLAPSE_AP = 4,
  GE_5X_COLLAPSE_SI = 5,
  GE_5X_COLLAPSE_PJN = 6,
  GE_5X_COLLAPSE_ALL = 7
};

enum GE_5X_SAT_TYPE_ENUM
{
  GE_5X_SAT_NONE = 0,
  GE_5X_SAT_FAT = 1,
  GE_5X_SAT_WATER = 2
};

enum GE_5X_GRX_TYPE_ENUM
{
  GE_5X_GRX_NONE = 0,
  GE_5X_GRX_LOC1 = 1,
  GE_5X_GRX_LOC2 = 2
};

enum GE_5X_IMG_MODE_ENUM
{
  GE_5X_IMG_2D = 0,
  GE_5X_IMG_3D = 2,
  GE_5X_IMG_3DFOURIER = 3,
  GE_5X_IMG_CINE = 4,
  GE_5X_IMG_ANGIO = 5,
  GE_5X_IMG_SPECT = 6,
  GE_5X_IMG_FLOURO = 7,
  GE_5X_IMG_RM = 8
};

enum GE_5X_SEQ_TYPE_ENUM
{
  GE_5X_SEQ_SE = 0,
  GE_5X_SEQ_IR = 1,
  GE_5X_SEQ_RM = 2,
  GE_5X_SEQ_RMGE = 3,
  GE_5X_SEQ_GRE = 4,
  GE_5X_SEQ_MPGR = 5,
  GE_5X_SEQ_MPIRS = 6,
  GE_5X_SEQ_MPIRI = 7,
  GE_5X_SEQ_VOGRE = 8,
  GE_5X_SEQ_CINEGRE = 9,
  GE_5X_SEQ_SPGR = 10,
  GE_5X_SEQ_SSFP = 11,
  GE_5X_SEQ_TOF = 12,
  GE_5X_SEQ_PC = 13,
  GE_5X_SEQ_CINE = 14,
  GE_5X_SEQ_TOFGR = 15,
  GE_5X_SEQ_TOFSPGR = 16,
  GE_5X_SEQ_PCGR = 17,
  GE_5X_SEQ_PCSPGR = 18,
  GE_5X_SEQ_FSE = 19,
  GE_5X_SEQ_FGR = 20,
  GE_5X_SEQ_FMPGR = 21,
  GE_5X_SEQ_FSPGR = 22,
  GE_5X_SEQ_FMPSPGR = 23,
  GE_5X_SEQ_SPECT = 24,
  GE_5X_SEQ_MIXED = 25
};

enum GE_5X_CT_GANTRY_ROT_ENUM
{
  GE_5X_CT_GANTRY_CW = 1,
  GE_5X_CT_GANTRY_CCW = 2
};

enum GE_5X_CT_ROT_SPEED_ENUM
{
  GE_5X_CT_ROT_SPEED_OFF = 1,
  GE_5X_CT_ROT_SPEED_LOW = 2,
  GE_5X_CT_ROT_SPEED_MED = 3,
  GE_5X_CT_ROT_SPEED_HIGH = 4
};

enum GE_5X_CT_TRIG_ENUM
{
  GE_5X_CT_TRIG_XTTX = 1,
  GE_5X_CT_TRIG_TT = 2,
  GE_5X_CT_TRIG_TXXT = 3,
  GE_5X_CT_TRIG_XXTT = 4
};

enum GE_5X_CT_FS_ENUM
{
  GE_5X_CT_FS_SMALL = 1,
  GE_5X_CT_FS_LARGE = 2
};

enum GE_5X_CT_SCOUT_ENUM
{
  GE_5X_CT_SCOUT_VERT = 1,
  GE_5X_CT_SCOUT_HORZ = 2
};

enum GE_5X_CT_PHANTOM_SIZE_ENUM
{
  GE_5X_CT_PHANTOM_SIZE_NONE = 1,
  GE_5X_CT_PHANTOM_SIZE_SMALL = 2,
  GE_5X_CT_PHANTOM_SIZE_MED = 3,
  GE_5X_CT_PHANTOM_SIZE_LARGE = 4
};

enum GE_5X_CT_PHANTOM_TYPE_ENUM
{
  GE_5X_CT_PHANTOM_TYPE_NONE = 1,
  GE_5X_CT_PHANTOM_TYPE_AIR = 2,
  GE_5X_CT_PHANTOM_TYPE_WATER = 3,
  GE_5X_CT_PHANTOM_TYPE_POLY = 4
};

enum GE_5X_CT_FILTER_TYPE_ENUM
{
  GE_5X_CT_FILTER_TYPE_AIR = 1,
  GE_5X_CT_FILTER_TYPE_BODY = 2,
  GE_5X_CT_FILTER_TYPE_BOWTIE = 3,
  GE_5X_CT_FILTER_TYPE_FLAT = 4,
  GE_5X_CT_FILTER_TYPE_HIGH = 5
};

enum GE_5X_CT_COMPUTE_TYPE_ENUM
{
  GE_5X_CT_COMPUTE_TYPE_AXIAL = 1,
  GE_5X_CT_COMPUTE_TYPE_CAL = 2,
  GE_5X_CT_COMPUTE_TYPE_SCOUT = 3,
  GE_5X_CT_COMPUTE_TYPE_PPSCAN = 4,
  GE_5X_CT_COMPUTE_TYPE_VIEWS = 5
};

enum GE_5X_ENTRY_TYPE_ENUM
{
  GE_5X_ENTRY_HEAD_FIRST = 1,
  GE_5X_ENTRY_FEET_FIRST = 2
};

enum GE_5X_SERIES_TYPE_ENUM
{
  GE_5X_SERIES_TYPE_PROSP = 1,
  GE_5X_SERIES_TYPE_RETRO = 2,
  GE_5X_SERIES_TYPE_SCOUT = 3,
  GE_5X_SERIES_TYPE_REFMT = 4,
  GE_5X_SERIES_TYPE_SSAVE = 5,
  GE_5X_SERIES_TYPE_XENON = 6,
  GE_5X_SERIES_TYPE_SERV = 7,
  GE_5X_SERIES_TYPE_PJN = 9
};

enum GE_5X_SCAN_TYPE_ENUM
{
  GE_5X_SCAN_TYPE_SCOUT = 1,
  GE_5X_SCAN_TYPE_AXIAL = 2,
  GE_5X_SCAN_TYPE_SSAVE = 3
};

enum GE_RELATIVE_STARTS
{
  GENESIS_SU_HDR_START = 0,
  GENESIS_EX_HDR_START = GENESIS_SU_HDR_LEN,
  GENESIS_SE_HDR_START = GENESIS_EX_HDR_START + GENESIS_EX_HDR_LEN,
  GENESIS_IM_HDR_START = GENESIS_SE_HDR_START + GENESIS_SE_HDR_LEN,
  GENESIS_IMG_HDR_START = 0
};

#endif /* __Ge5xHdr_h */
