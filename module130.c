#include <stdio.h>
#include <math.h>

#define Y 140
#define S 3
#define G 115
#define D 80
#define E 40

// #define STARTY 2018               // 추계시작연도
// #define ENDY 2100                 // 추계종료연도
#define SUMS 0
#define UPAGE G - 2
#define SUMAGE G - 1
#define SUMD D - 1
#define SUME E - 1

#define ADJ1 0.0  // Hd & New Adj
#define ADJ2 1.0  // RtNew Adj
#define ADJ3 1.00 // Safety Margin for Early Oldage Pension

#define UB 0.0000011
#define LB -0.0000011

#define LinkYear 2008

main()
{
	int i, j, k, y, s, g, d, e, gc, d1, d2, FileCheck;

	int itemp[Y];
	double dtemp[Y], ftemp[Y];
	int STARTY, ENDY, MG;
	char skip_chr, skip_line[500];

	static int AgeIns[Y + 1], Status[6][Y], MinAge[6][Y], MinDura[6][Y], MaxAge[6][Y], MaxDura[6][Y];
	static double RtWkWk[Y][S][G], RtWkRe[Y][S][G], RtWkHd[Y][S][G];
	static double RtReWk[Y][S][G], RtReRe[Y][S][G], RtReHd[Y][S][G];
	static double RtHdWk[Y][S][G], RtHdRe[Y][S][G], RtHdHd[Y][S][G];
	static double RtNewWk[Y][S][G], RtNewRe[Y][S][G];

	static double NmWkPar[Y][S][G], NmRePar[Y][S][G], NmHdPar[Y][S][G];
	static double NmWkParN[Y][S][G], NmReParN[Y][S][G], NmHdParN[Y][S][G];
	static double NmWkParSum[Y][S][G], NmReParSum[Y][S][G], NmHdParSum[Y][S][G];
	static double TnWkPar[Y][S][G], TnRePar[Y][S][G], TnHdPar[Y][S][G];

	static double NmNewWk[Y][S][G], NmNewRe[Y][S][G];
	static double NmNewWkpsm[Y][S][G], NmNewRepsm[Y][S][G];
	static double TempNmNewWk[Y][S][G], TempNmNewRe[Y][S][G];
	static double NmWkWk[Y][S][G], NmWkRe[Y][S][G], NmWkHd[Y][S][G];
	static double NmReWk[Y][S][G], NmReRe[Y][S][G], NmReHd[Y][S][G];
	static double NmHdWk[Y][S][G], NmHdRe[Y][S][G], NmHdHd[Y][S][G];

	static double RtAbr[S][G], RtOth[Y][S][G];
	static double NmOut[Y][S][G], RtOut[Y][S][G];
	static double NmAbr[Y][S][G], NmDeath[Y][S][G], NmOth[Y][S][G];
	static double NmNpsGov[Y][S][G], NmNpsPst[Y][S][G], NmNpsSol[Y][S][G];
	static double NmWkGov[Y][S][G], NmReGov[Y][S][G], NmHdGov[Y][S][G];
	static double NmWkPst[Y][S][G], NmRePst[Y][S][G], NmHdPst[Y][S][G];
	static double NmWkSol[Y][S][G], NmReSol[Y][S][G], NmHdSol[Y][S][G];

	static double TempWkWk[Y][S][G], TempWkRe[Y][S][G], TempWkHd[Y][S][G];
	static double TempReWk[Y][S][G], TempReRe[Y][S][G], TempReHd[Y][S][G];
	static double TempHdWk[Y][S][G], TempHdRe[Y][S][G], TempHdHd[Y][S][G];
	static double TempNmHdPar[Y][S][G];

	static double Pop[Y][S][G], RtDeath[Y][S][G], NmOther[Y][S][G];

	static double TnNmGov[Y][S][G], NmGov[Y][S][G][E], IniTnGov[Y][S][G], TempNmGov[Y][S][G][E];
	static double TempNmGovOver[Y][S][G];
	static double NmGovOut[Y][S][G][E], NmGovOutOver[S][G][E], TotNmGovOut[Y];
	static double NmGovNps[Y][S][G][E];

	static double TnNmPst[Y][S][G], NmPst[Y][S][G][E], IniTnPst[Y][S][G], TempNmPst[Y][S][G][E];
	static double TempNmPstOver[Y][S][G];
	static double NmPstOut[Y][S][G][E], NmPstOutOver[S][G][E], TotNmPstOut[Y];
	static double NmPstNps[Y][S][G][E];

	static double TnNmSol[Y][S][G], NmSol[Y][S][G][E], IniTnSol[Y][S][G], TempNmSol[Y][S][G][E];
	static double TempNmSolOver[Y][S][G];
	static double NmSolOut[Y][S][G][E], NmSolOutOver[S][G][E], TotNmSolOut[Y];
	static double NmSolNps[Y][S][G][E];
	static double PsmNmSol[Y][S][G][D][E];
	static double PsmNmSol1[Y][S][G][D][E];

	static double NmGovWk[Y][S][G], NmGovRe[Y][S][G], NmGovHd[Y][S][G];
	static double NmPstWk[Y][S][G], NmPstRe[Y][S][G], NmPstHd[Y][S][G];
	static double NmSolWk[Y][S][G], NmSolRe[Y][S][G], NmSolHd[Y][S][G];

	static double RtGovOut[Y][S][G][E], RtPstOut[Y][S][G][E], RtSolOut[Y][S][G][E];
	static double RtGovOutIni[Y][S][G][E], RtPstOutIni[Y][S][G][E], RtSolOutIni[Y][S][G][E];
	static double RtGovOutNps[Y][S][G][E], RtPstOutNps[Y][S][G][E], RtSolOutNps[Y][S][G][E];
	static double RtGovWk[Y][S][G], RtGovRe[Y][S][G];
	static double RtPstWk[Y][S][G], RtPstRe[Y][S][G];
	static double RtSolWk[Y][S][G], RtSolRe[Y][S][G];

	static double RtNpsGov[Y][S][G], RtNpsPst[Y][S][G], RtNpsSol[Y][S][G];
	static double RtOthIni[Y][S][G], RtNpsGovIni[Y][S][G], RtNpsPstIni[Y][S][G], RtNpsSolIni[Y][S][G];

	static double RtNewSol[S][G];

	FILE *fp1, *fp4, *fp5, *fp6, *fp7;
	FILE *fp13, *fp14, *fp16, *fp17, *fp19;
	FILE *fp24, *fp25, *fp26, *fp27, *fp28;
	FILE *fp41, *fp42, *fp43;
	FILE *fp57;

	FILE *fp501;
	FILE *fp539;
	FILE *fp603, *fp639;
	FILE *fp_sim;

	// read sim.input
	fp_sim = fopen("/work2/n1220186/Project2024_max/source/sim.input", "r");

	// read tdata
	fp5 = fopen("/work2/n1220186/Project2024_max/tdata/master_f.dat", "r");	 // 사업장 마스터 화일
	fp42 = fopen("/work2/n1220186/Project2024_max/tdata/nppmo120d20t", "r"); // 가입자(y,s,g) temporary

	// read sdata
	fp1 = fopen("/work2/n1220186/Project2024_max/sdata/Gpop.dat", "r");				   // 인구 통계청 2016 ver
	fp4 = fopen("/work2/n1220186/Project2024_max/sdata/Par_ysgd.dat", "r");			   // 국민연금가입자 및 대기자 2016이력자료
	fp6 = fopen("/work2/n1220186/Project2024_max/sdata/RtAbr2021_sgd.dat", "r");	   // 국외이주율 2021
	fp7 = fopen("/work2/n1220186/Project2024_max/sdata/RtDeath.dat", "r");			   // 사망률 통계청 2016 Lx감소율
	fp41 = fopen("/work2/n1220186/Project2024_max/sdata/Task2019_Ratio_11t.txt", "r"); // 연간 이동율 실적자료 2019
	fp43 = fopen("/work2/n1220186/Project2024_max/sdata/RtNewAdj2019.txt", "r");	   // 신규가입자 비율(비가입자 대비) - 4차
	fp13 = fopen("/work2/n1220186/Project2024_max/sdata/NpsOcc2020.dat", "r");		   // 국민연금에서 직역연금으로의 이동자 2020
	fp24 = fopen("/work2/n1220186/Project2024_max/sdata/RtOthKindWeight_2019", "r");   // 직역연금 이동자의 각 직역연금별 비중 2019
	fp14 = fopen("/work2/n1220186/Project2024_max/sdata/Oth-Npc-Rate_2019", "r");	   // 직역연금퇴직자의 국민연금 재가입률 2019
	fp16 = fopen("/work2/n1220186/Project2024_max/sdata/NmGov_YSG.dat", "r");		   // 공무원연금가입자 전망치(y,s,g)
	fp19 = fopen("/work2/n1220186/Project2024_max/sdata/NmPst_YSG.dat", "r");		   // 사학연금가입자 전망치(y,s,g)
	fp27 = fopen("/work2/n1220186/Project2024_max/sdata/Occ_sgde.dat", "r");		   // 직역(공무원,사학,군인)연금가입자(y,s,g,d,e)
	fp17 = fopen("/work2/n1220186/Project2024_max/sdata/OccNps2020.dat", "r");		   // 직역연금 가입자 이동률 2020
	fp25 = fopen("/work2/n1220186/Project2024_max/sdata/RtNewSol.dat", "r");		   // 군인연금 신규가입자 성별연령별 비중
	fp26 = fopen("/work2/n1220186/Project2024_max/sdata/RtSolCon.dat", "r");
	fp28 = fopen("/work2/n1220186/Project2024_max/sdata/NmSol2017.dat", "r");

	// write tdata
	fp501 = fopen("/work2/n1220186/Project2024_max/tdata/nppmo130d501t", "w"); // 가입자 이동률(NPS) -> nppm135
	fp603 = fopen("/work2/n1220186/Project2024_max/tdata/nppmo130d603t", "w"); // 가입자 이동률(OCC) -> nppm135
	fp539 = fopen("/work2/n1220186/Project2024_max/tdata/nppmo130d539t", "w"); // 신규가입자         -> nppm135
	fp639 = fopen("/work2/n1220186/Project2024_max/tdata/nppmo130d639t", "w"); // 신규가입자비율     -> nppm135

	// 시뮬레이션 변수 scan
	for (j = 1; j <= 4; j++)
		for (i = 1; i <= 1; i++)
			fgets(skip_line, 500, fp_sim);
	for (i = 1; i <= 41; i++)
		fscanf(fp_sim, "%c", &skip_chr);
	fscanf(fp_sim, "%d  \n", &STARTY);
	for (i = 1; i <= 41; i++)
		fscanf(fp_sim, "%c", &skip_chr);
	fscanf(fp_sim, "%d  \n", &ENDY);

	STARTY = 2022;

	// 마스터 화일 입력
	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp5, "%d %lf %d", &itemp[1], &dtemp[1], &itemp[2]);
		if (FileCheck == EOF)
			break;
		y = itemp[1] - 1987;
		AgeIns[y] = itemp[2];
		for (i = 1; i <= 5; i++)
		{
			fscanf(fp5, "%d %d %d %d %d",
				   &Status[i][y], &MinAge[i][y], &MaxAge[i][y], &MinDura[i][y], &MaxDura[i][y]);
		}
		fscanf(fp5, "\n");
	}

	// 인구 입력
	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp1, "%d %d", &itemp[1], &itemp[2]);
		if (FileCheck == EOF)
			break;
		y = itemp[1] - 1987;
		g = itemp[2];
		fscanf(fp1, "%lf %lf\n", &Pop[y][1][g], &Pop[y][2][g]);
	}

	// 사망율 입력
	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp7, "%d %d", &itemp[1], &itemp[2]);
		if (FileCheck == EOF)
			break;
		y = itemp[1] - 1987;
		g = itemp[2];
		fscanf(fp7, "%lf %lf\n", &RtDeath[y][1][g], &RtDeath[y][2][g]);
	}

	// 180605
	for (y = 1988 - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			for (g = 106; g <= UPAGE; g++)
			{
				RtDeath[y][s][g] = 1.0;
			}
		}
	}
	for (y = 2101 - 1987; y <= ENDY - 1987; y++)
	{
		for (g = 0; g <= UPAGE; g++)
		{
			RtDeath[y][1][g] = RtDeath[2100 - 1987][1][g];
			RtDeath[y][2][g] = RtDeath[2100 - 1987][2][g];
		}
	}

	// 가입자 입력(y, s, g) from nppm120
	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp42, "%d %d", &itemp[1], &itemp[2]);
		if (FileCheck == EOF)
			break;
		y = itemp[1] - 1987;
		g = itemp[2];
		fscanf(fp42, "%lf %lf %lf %lf %lf %lf\n",
			   &dtemp[3], &TnWkPar[y][1][g], &TnWkPar[y][2][g], &dtemp[6], &TnRePar[y][1][g], &TnRePar[y][2][g]);
		NmWkPar[y][1][g] = TnWkPar[y][1][g];
		NmWkPar[y][2][g] = TnWkPar[y][2][g];
		NmRePar[y][1][g] = TnRePar[y][1][g];
		NmRePar[y][2][g] = TnRePar[y][2][g];
	}

	// 대기자 입력
	k = 0;
	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp4, "%d %d %d", &itemp[1], &itemp[2], &itemp[3]);
		if (FileCheck == EOF)
			break;
		y = itemp[1] - 1987;
		s = itemp[2];
		g = itemp[3];
		if (y == 1988 - 1987 && s == 1 && g == 18)
			k++;
		for (d = 0; d <= STARTY - 1987; d++)
		{
			// for(d=0; d<=STARTY-1-1987; d++){
			fscanf(fp4, "%lf", &dtemp[4]);
			if (k == 1 && g > 59 && d > 0)
				NmHdPar[y][s][g] += dtemp[4];
			if (k == 2 && g > 59 && d > 0)
				NmHdPar[y][s][g] += dtemp[4];
			if (y < 2013 - 1987 && k == 3 && g <= 59 && d > 0)
				NmHdPar[y][s][g] += dtemp[4];
			if (y >= 2013 - 1987 && y < 2018 - 1987 && k == 3 && g <= 60 && d > 0)
				NmHdPar[y][s][g] += dtemp[4];
			if (y >= 2018 - 1987 && y < 2023 - 1987 && k == 3 && g <= 61 && d > 0)
				NmHdPar[y][s][g] += dtemp[4];
		}
		fscanf(fp4, "\n");
	}

	// y, s, g별 가입자 출력
	for (y = STARTY - 1 - 1987; y <= STARTY - 1 - 1987; y++)
	{
		dtemp[1] = 0.0;
		dtemp[2] = 0.0;
		dtemp[3] = 0.0;
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 59; g++)
			{
				dtemp[1] += NmWkPar[y][s][g];
				dtemp[2] += NmRePar[y][s][g];
				dtemp[3] += NmHdPar[y][s][g];
			}
		}
	}

	// Adjust1
	for (y = STARTY - 1 - 1987; y <= STARTY - 1 - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			// 5th
			// for(g=18; g<=59; g++)
			for (g = 18; g <= AgeIns[y]; g++)
			{
				dtemp[95] = Pop[y][s][g] - (NmWkPar[y][s][g] + NmRePar[y][s][g] + NmHdPar[y][s][g]);
				if (dtemp[95] < 0.0)
				{
					NmHdPar[y][s][g] += dtemp[95];
				}
			}
		}
	}

	// 연간 이동율 입력
	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp41, "%d %d", &s, &g);
		if (FileCheck == EOF)
			break;
		fscanf(fp41, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
			   &RtWkWk[1][s][g], &RtWkRe[1][s][g], &RtWkHd[1][s][g],
			   &RtReWk[1][s][g], &RtReRe[1][s][g], &RtReHd[1][s][g],
			   &RtHdWk[1][s][g], &RtHdRe[1][s][g], &RtHdHd[1][s][g],
			   &RtNewWk[1][s][g], &RtNewRe[1][s][g]);
	}
	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp43, "%d %d", &s, &g);
		if (FileCheck == EOF)
			break;
		fscanf(fp43, "%lf %lf \n", &dtemp[1], &dtemp[2]);
		RtNewWk[1][s][g] = dtemp[1];
		RtNewRe[1][s][g] = dtemp[2];
	}
	for (y = 1989 - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			// 5th adjusted
			// for(g=18; g<=59; g++)
			// for(g=18; g<=MaxAge[1][y]; g++)
			// for(g=18; g<=AgeIns[y]; g++)
			if (AgeIns[y + 1] > AgeIns[y])
				MG = AgeIns[y + 1] - 1;
			else
				MG = AgeIns[y];
			for (g = 18; g <= MG; g++)
			{
				RtWkWk[y][s][g] = RtWkWk[1][s][g];
				RtWkRe[y][s][g] = RtWkRe[1][s][g];
				RtWkHd[y][s][g] = RtWkHd[1][s][g];
				RtReWk[y][s][g] = RtReWk[1][s][g];
				RtReRe[y][s][g] = RtReRe[1][s][g];
				RtReHd[y][s][g] = RtReHd[1][s][g];
				RtHdWk[y][s][g] = RtHdWk[1][s][g];
				RtHdRe[y][s][g] = RtHdRe[1][s][g];
				RtHdHd[y][s][g] = RtHdHd[1][s][g];
				RtNewWk[y][s][g] = RtNewWk[1][s][g] * ADJ2;
				RtNewRe[y][s][g] = RtNewRe[1][s][g] * ADJ2;
				if (g == 18)
				{
					RtNewWk[y][s][g] = 1.0;
					RtNewRe[y][s][g] = 1.0;
				}
				// 5th
				if (g >= 60)
				{
					RtNewWk[y][s][g] = 0.0;
					RtNewRe[y][s][g] = 0.0;
				}
			}
		}
	}
	for (y = 1988 - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			// 5th adjusted
			// for(g=18; g<=59; g++)
			// for(g=18; g<=MaxAge[1][y]; g++)
			// for(g=18; g<=AgeIns[y]; g++)
			if (AgeIns[y + 1] > AgeIns[y])
				MG = AgeIns[y + 1] - 1;
			else
				MG = AgeIns[y];
			for (g = 18; g <= MG; g++)
			{
				// 5th adjusted
				// if(g==59)
				if ((g >= MG && MG == AgeIns[y + 1]) || (y == ENDY - 1987 && g == MG))
				{
					RtWkWk[y][s][g] = 0.0;
					RtWkRe[y][s][g] = 0.0;
					RtWkHd[y][s][g] = 1.0;
					RtReWk[y][s][g] = 0.0;
					RtReRe[y][s][g] = 0.0;
					RtReHd[y][s][g] = 1.0;
					RtHdWk[y][s][g] = 0.0;
					RtHdRe[y][s][g] = 0.0;
					RtHdHd[y][s][g] = 1.0;
				}
				dtemp[1] = RtWkWk[y][s][g] + RtWkRe[y][s][g] + RtWkHd[y][s][g];
				dtemp[2] = RtReWk[y][s][g] + RtReRe[y][s][g] + RtReHd[y][s][g];
				dtemp[3] = RtHdWk[y][s][g] + RtHdRe[y][s][g] + RtHdHd[y][s][g];

				RtWkWk[y][s][g] = RtWkWk[y][s][g] / dtemp[1];
				RtWkRe[y][s][g] = RtWkRe[y][s][g] / dtemp[1];
				RtWkHd[y][s][g] = RtWkHd[y][s][g] / dtemp[1];

				RtReWk[y][s][g] = RtReWk[y][s][g] / dtemp[2];
				RtReRe[y][s][g] = RtReRe[y][s][g] / dtemp[2];
				RtReHd[y][s][g] = RtReHd[y][s][g] / dtemp[2];

				RtHdWk[y][s][g] = RtHdWk[y][s][g] / dtemp[3];
				RtHdRe[y][s][g] = RtHdRe[y][s][g] / dtemp[3];
				RtHdHd[y][s][g] = RtHdHd[y][s][g] / dtemp[3];
			}
		}
	}

	// NpsOcc2020.dat
	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp13, "%d", &g);
		if (FileCheck == EOF)
			break;
		fscanf(fp13, "%lf %lf %lf %lf %lf %lf %lf %lf\n",
			   &RtOth[1][1][g], &RtOth[1][2][g],
			   &RtNpsGov[1][1][g], &RtNpsPst[1][1][g], &RtNpsSol[1][1][g],
			   &RtNpsGov[1][2][g], &RtNpsPst[1][2][g], &RtNpsSol[1][2][g]);
	}
	for (y = 2000 - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 59; g++)
			{
				RtOth[y][s][g] = RtOth[1][s][g];
				RtNpsGov[y][s][g] = RtNpsGov[1][s][g];
				RtNpsPst[y][s][g] = RtNpsPst[1][s][g];
				RtNpsSol[y][s][g] = RtNpsSol[1][s][g];
			}
		}
	}
	for (y = 2000 - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 59; g++)
			{
				RtOthIni[y][s][g] = RtOth[y][s][g];
				RtNpsGovIni[y][s][g] = RtNpsGov[y][s][g];
				RtNpsPstIni[y][s][g] = RtNpsPst[y][s][g];
				RtNpsSolIni[y][s][g] = RtNpsSol[y][s][g];
			}
		}
	}

	// RtAbr2021.dat
	for (i = 1;; i++)
	{
		FileCheck = fscanf(fp6, "%d %d", &itemp[1], &itemp[2]);
		if (FileCheck == EOF)
			break;
		for (j = 18; j <= 59; j++)
		{
			fscanf(fp6, "%lf", &dtemp[1]);
			// if(itemp[2]==50) RtAbr[itemp[1]][j]=dtemp[1];
			if (itemp[2] == 0)
				RtAbr[itemp[1]][j] = dtemp[1];
		}
		fscanf(fp6, "\n");
	}
	// RtAbr 2021 끝

	// 이동률 출력
	for (y = 2000 - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			// 5th adjusted
			// for(g=18; g<=59; g++)
			for (g = 18; g <= AgeIns[y]; g++)
			// for(g=18; g<=MaxAge[1][y]; g++)
			{
				RtOut[y][s][g] = RtDeath[y][s][g] + RtAbr[s][g] + RtOth[y][s][g];

				// 수정검토요망(180801)
				RtWkHd[y][s][g] = RtWkHd[y][s][g] - RtOut[y][s][g];
				RtReHd[y][s][g] = RtReHd[y][s][g] - RtOut[y][s][g];
				RtHdHd[y][s][g] = RtHdHd[y][s][g] - RtOut[y][s][g];

				if (RtWkHd[y][s][g] < 0.0)
					RtWkHd[y][s][g] = 0.0;
				if (RtReHd[y][s][g] < 0.0)
					RtReHd[y][s][g] = 0.0;
				if (RtHdHd[y][s][g] < 0.0)
					RtHdHd[y][s][g] = 0.0;
			}
		}
	}

	// 연계관련 기초자료 입력 시작

	//	직역연금 이동률 입력(20200803)

	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp17, "%d", &g);
		if (FileCheck == EOF)
			break;
		fscanf(fp17, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
			   &RtGovOut[1][1][g][0], &RtGovOutNps[1][1][g][0], &RtGovWk[1][1][g], &RtGovRe[1][1][g],
			   &RtGovOut[1][2][g][0], &RtGovOutNps[1][2][g][0], &RtGovWk[1][2][g], &RtGovRe[1][2][g],
			   &RtPstOut[1][1][g][0], &RtPstOutNps[1][1][g][0], &RtPstWk[1][1][g], &RtPstRe[1][1][g],
			   &RtPstOut[1][2][g][0], &RtPstOutNps[1][2][g][0], &RtPstWk[1][2][g], &RtPstRe[1][2][g],
			   &RtSolOut[1][1][g][0], &RtSolOutNps[1][1][g][0], &RtSolWk[1][1][g], &RtSolRe[1][1][g],
			   &RtSolOut[1][2][g][0], &RtSolOutNps[1][2][g][0], &RtSolWk[1][2][g], &RtSolRe[1][2][g]);
	}

	for (y = 1988 - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 59; g++)
			{
				for (e = 0; e <= E - 1; e++)
				{
					RtGovOut[y][s][g][e] = RtGovOut[1][s][g][0];
					RtGovOutNps[y][s][g][e] = RtGovOutNps[1][s][g][0];
					RtPstOut[y][s][g][e] = RtPstOut[1][s][g][0];
					RtPstOutNps[y][s][g][e] = RtPstOutNps[1][s][g][0];
					RtSolOut[y][s][g][e] = RtSolOut[1][s][g][0];
					RtSolOutNps[y][s][g][e] = RtSolOutNps[1][s][g][0];
				}
				RtGovWk[y][s][g] = RtGovWk[1][s][g];
				RtGovRe[y][s][g] = RtGovRe[1][s][g];
				RtPstWk[y][s][g] = RtPstWk[1][s][g];
				RtPstRe[y][s][g] = RtPstRe[1][s][g];
				RtSolWk[y][s][g] = RtSolWk[1][s][g];
				RtSolRe[y][s][g] = RtSolRe[1][s][g];
			}
		}
	}

	for (y = 1988 - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 59; g++)
			{
				for (e = 0; e <= E - 1; e++)
				{
					RtGovOutIni[y][s][g][e] = RtGovOut[y][s][g][e];
					RtPstOutIni[y][s][g][e] = RtPstOut[y][s][g][e];
					RtSolOutIni[y][s][g][e] = RtSolOut[y][s][g][e];
				}
			}
		}
	}

	// 직역연금 가입자 실적(201712기준, y, s, g, d, e)

	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp27, "%d %d %d %d %lf %lf %lf\n", &s, &g, &d, &e, &dtemp[1], &dtemp[2], &dtemp[3]);
		if (FileCheck == EOF)
			break;
		if (e > E - 2)
			e = E - 2;
		NmGov[STARTY - 1 - 1987][s][g][e] += dtemp[1];
		NmPst[STARTY - 1 - 1987][s][g][e] += dtemp[2];
		NmSol[STARTY - 1 - 1987][s][g][e] += dtemp[3];
		PsmNmSol[STARTY - 1 - 1987][s][g][d][e] += dtemp[3];
	}
	for (y = STARTY - 1 - 1987; y <= STARTY - 1 - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 64; g++)
			{
				for (e = 0; e <= E - 2; e++)
				{
					NmGov[y][s][g][SUME] += NmGov[y][s][g][e];
					NmGov[y][s][SUMAGE][SUME] += NmGov[y][s][g][e];
					NmGov[y][SUMS][SUMAGE][SUME] += NmGov[y][s][g][e];
					NmPst[y][s][g][SUME] += NmPst[y][s][g][e];
					NmPst[y][s][SUMAGE][SUME] += NmPst[y][s][g][e];
					NmPst[y][SUMS][SUMAGE][SUME] += NmPst[y][s][g][e];
					NmSol[y][s][g][SUME] += NmSol[y][s][g][e];
					NmSol[y][s][SUMAGE][SUME] += NmSol[y][s][g][e];
					NmSol[y][SUMS][SUMAGE][SUME] += NmSol[y][s][g][e];
				}
			}
		}
	}

	// 직역연금 실적(60세 이상 검토요망)_180801
	// 공무원연금관련 자료 입력 시작
	// 공무원연금 가입자 전망치 입력(y,s,g)

	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp16, "%d %d", &itemp[1], &g);
		if (FileCheck == EOF)
			break;
		y = itemp[1] - 1987;
		fscanf(fp16, "%lf %lf\n", &TnNmGov[y][1][g], &TnNmGov[y][2][g]);
	}
	for (y = 2091 - 1987; y <= ENDY - 1987; y++)
	{ // 180703 수정
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 64; g++)
			{
				TnNmGov[y][s][g] = TnNmGov[y - 1][s][g];
			}
		}
	}
	for (y = STARTY - 1 - 1987; y <= STARTY - 1 - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 64; g++)
			{
				dtemp[1] = 0.0;
				for (e = 0; e <= E - 2; e++)
					dtemp[1] += NmGov[y][s][g][e];
				for (e = 0; e <= E - 2; e++)
				{
					if (dtemp[1] > 0.0)
						NmGov[y][s][g][e] = TnNmGov[y][s][g] * (NmGov[y][s][g][e] / dtemp[1]);
				}
			}
		}
	}

	// 공무원연금관련 자료 입력 종료

	// 사학연금관련 자료 입력 시작

	// 사학연금 가입자 전망치 입력(y,s,g)

	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp19, "%d %d %d %lf \n", &itemp[1], &itemp[2], &itemp[3], &dtemp[1]);
		if (FileCheck == EOF)
			break;
		y = itemp[1] - 1987;
		s = itemp[2];
		g = itemp[3];
		TnNmPst[y][s][g] = dtemp[1];
	}
	for (y = 2071 - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 64; g++)
			{
				TnNmPst[y][s][g] = TnNmPst[y - 1][s][g];
			}
		}
	}
	for (y = STARTY - 1 - 1987; y <= STARTY - 1 - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 64; g++)
			{
				dtemp[2] = 0.0;
				for (e = 0; e <= E - 2; e++)
					dtemp[2] += NmPst[y][s][g][e];
				for (e = 0; e <= E - 2; e++)
				{
					if (dtemp[2] > 0.0)
						NmPst[y][s][g][e] = TnNmPst[y][s][g] * (NmPst[y][s][g][e] / dtemp[2]);
				}
			}
		}
	}

	// 사학연금관련 자료 입력 종료

	// 군인연금관련 자료 입력 시작

	// 군인연금 가입자 전망치 입력(t,s,g)
	// 군인연금 가입자 실적(2021년 군인연금 통계연보 기준)
	TnNmSol[2011 - 1987][SUMS][SUMAGE] = 173497.0;
	TnNmSol[2012 - 1987][SUMS][SUMAGE] = 180478.0;
	TnNmSol[2013 - 1987][SUMS][SUMAGE] = 182443.0;
	TnNmSol[2014 - 1987][SUMS][SUMAGE] = 183367.0;
	TnNmSol[2015 - 1987][SUMS][SUMAGE] = 183064.0;
	TnNmSol[2016 - 1987][SUMS][SUMAGE] = 182958.0;
	TnNmSol[2017 - 1987][SUMS][SUMAGE] = 182054.0;
	TnNmSol[2018 - 1987][SUMS][SUMAGE] = 183365.0;
	TnNmSol[2019 - 1987][SUMS][SUMAGE] = 187051.0;
	TnNmSol[2020 - 1987][SUMS][SUMAGE] = 190086.0;
	TnNmSol[2021 - 1987][SUMS][SUMAGE] = 192199.0;

	// 군인연금 가입자 전망(군연연금과 제공 22.07.05)
	TnNmSol[2022 - 1987][SUMS][SUMAGE] = 190827.0;
	TnNmSol[2023 - 1987][SUMS][SUMAGE] = 192737.0;
	TnNmSol[2024 - 1987][SUMS][SUMAGE] = 193302.0;
	TnNmSol[2025 - 1987][SUMS][SUMAGE] = 193396.0;
	TnNmSol[2026 - 1987][SUMS][SUMAGE] = 194241.0;

	for (y = 2027 - 1987; y <= ENDY - 1987; y++)
		TnNmSol[y][SUMS][SUMAGE] = 194513.0; // 220705 수정

	//	2020.5.8 edit

	for (y = STARTY - 1 - 1987; y <= STARTY - 1 - 1987; y++)
	{
		dtemp[3] = 0.0;
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 64; g++)
			{
				for (e = 0; e <= E - 2; e++)
					dtemp[3] += NmSol[STARTY - 1 - 1987][s][g][e];
			}
		}
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 64; g++)
			{
				for (e = 0; e <= E - 2; e++)
				{
					if (dtemp[3] > 0.0)
						NmSol[y][s][g][e] = TnNmSol[y][SUMS][SUMAGE] * (NmSol[STARTY - 1 - 1987][s][g][e] / dtemp[3]);
				}
			}
		}
	}

	for (y = STARTY - 1 - 1987; y <= STARTY - 1 - 1987; y++)
	{
		NmSol[y][SUMS][SUMAGE][SUME] = 0.0;
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 64; g++)
			{
				NmSol[y][s][g][SUME] = 0.0;
				for (e = 0; e <= E - 2; e++)
				{
					NmSol[y][SUMS][SUMAGE][SUME] += NmSol[y][s][g][e];
					NmSol[y][s][g][SUME] += NmSol[y][s][g][e];
				}
			}
		}
	}

	//	2020.5.8 edit end

	//	2020.5.25 edit

	for (y = STARTY - 1 - 1987; y <= STARTY - 1 - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 64; g++)
			{
				TnNmSol[y][s][g] = TnNmSol[y][SUMS][SUMAGE] * (NmSol[STARTY - 1 - 1987][s][g][SUME] / NmSol[STARTY - 1 - 1987][SUMS][SUMAGE][SUME]);
			}
		}
	}
	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp28, "%d %lf %lf\n", &g, &dtemp[1], &dtemp[2]);
		if (FileCheck == EOF)
			break;
		TnNmSol[STARTY - 1 - 1987][1][g] = dtemp[1];
		TnNmSol[STARTY - 1 - 1987][2][g] = dtemp[2];
	}
	for (y = STARTY - 1 - 1987; y <= STARTY - 1 - 1987; y++)
	{
		dtemp[1] = 0.0;
		dtemp[2] = 0.0;
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 64; g++)
			{
				dtemp[s] += TnNmSol[y][s][g];
			}
		}
	}
	for (y = STARTY - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			TnNmSol[y][s][SUMAGE] = TnNmSol[y][SUMS][SUMAGE] * dtemp[s] / (dtemp[1] + dtemp[2]);
		}
	}

	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp25, "%d %lf %lf\n", &g, &dtemp[1], &dtemp[2]);
		if (FileCheck == EOF)
			break;
		RtNewSol[1][g] = dtemp[1];
		RtNewSol[2][g] = dtemp[2];
	}
	for (j = 1;; j++)
	{
		FileCheck = fscanf(fp26, "%d %lf %lf\n", &g, &dtemp[1], &dtemp[2]);
		if (FileCheck == EOF)
			break;
		RtSolOut[STARTY - 1 - 1987][1][g][0] = 1.0 - dtemp[1];
		RtSolOut[STARTY - 1 - 1987][2][g][0] = 1.0 - dtemp[2];
	}
	for (y = STARTY - 1 - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			for (g = 60; g <= 64; g++)
			{
				for (e = 0; e <= E - 1; e++)
				{
					RtSolOut[y][s][g][e] = RtSolOut[STARTY - 1 - 1987][s][g][0] * 1.3;
				}
			}
		}
	}

	for (y = STARTY - 1987; y <= ENDY - 1987; y++)
	{
		dtemp[1] = 0.0;
		dtemp[2] = 0.0;
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 64; g++)
			{
				dtemp[s] += TnNmSol[y - 1][s][g - 1] * (1.0 - RtSolOut[y - 1][s][g - 1][0]);
			}
		}
		for (s = 1; s <= 2; s++)
			dtemp[s + 2] = TnNmSol[y][s][SUMAGE] - dtemp[s];
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 64; g++)
			{
				TnNmSol[y][s][g] = TnNmSol[y - 1][s][g - 1] * (1.0 - RtSolOut[y - 1][s][g - 1][0]) + dtemp[s + 2] * RtNewSol[s][g];
			}
		}
	}

	for (y = STARTY - 1 - 1987; y <= STARTY - 1 - 1987; y++)
	{
		dtemp[2] = 0.0;
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 59; g++)
			{
				dtemp[1] = 0.0;
				for (d = 0; d <= D - 2; d++)
				{
					for (e = 0; e <= E - 2; e++)
					{
						dtemp[1] += PsmNmSol[y][s][g][d][e];
					}
				}
				for (d = 0; d <= D - 2; d++)
				{
					for (e = 0; e <= E - 2; e++)
					{
						if (dtemp[1] != 0.0)
							PsmNmSol1[y][s][g][d][e] += TnNmSol[y][s][g] * PsmNmSol[y][s][g][d][e] / dtemp[1];
						else
							PsmNmSol1[y][s][g][d][e] = 0.0;
					}
				}
			}
		}
		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 59; g++)
			{
				for (d = 0; d <= D - 2; d++)
				{
					for (e = 0; e <= E - 2; e++)
					{
						if (PsmNmSol1[y][s][g][d][e] > 0.0)
							dtemp[2] += PsmNmSol1[y][s][g][d][e];
					}
				}
			}
		}

		for (s = 1; s <= 2; s++)
		{
			for (g = 18; g <= 59; g++)
			{
				for (e = 0; e <= E - 2; e++)
				{
					dtemp[1] = 0.0;
					for (d = 0; d <= D - 2; d++)
					{
						dtemp[1] += PsmNmSol1[y][s][g][d][e];
					}
					NmSol[y][s][g][e] = dtemp[1];
				}
			}
		}
	}


	//	2020.5.25 edit end

	// 군인연금관련 자료 입력 종료

	// 연계관련 기초자료 입력 종료

	// 신규가입자 및 가입자 이동률 재산출 //

	for (y = STARTY - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			// 5th
			if (AgeIns[y + 1] > AgeIns[y])
				MG = AgeIns[y + 1] - 1;
			else
				MG = AgeIns[y];
			// for(g=18; g<=MaxAge[1][y]; g++)
			// for(g=18; g<=AgeIns[y]; g++)
			for (g = 18; g <= MG; g++)
			{
				if (MG > AgeIns[y] && g > AgeIns[y])
				{
					RtWkWk[y - 1][s][g - 1] = RtWkWk[y - 1][s][g - 2];
					RtReWk[y - 1][s][g - 1] = RtReWk[y - 1][s][g - 2];
					RtHdWk[y - 1][s][g - 1] = RtHdWk[y - 1][s][g - 2];
					RtWkRe[y - 1][s][g - 1] = RtWkRe[y - 1][s][g - 2];
					RtReRe[y - 1][s][g - 1] = RtReRe[y - 1][s][g - 2];
					RtHdRe[y - 1][s][g - 1] = RtHdRe[y - 1][s][g - 2];
					RtWkHd[y - 1][s][g - 1] = RtWkHd[y - 1][s][g - 2];
					RtReHd[y - 1][s][g - 1] = RtReHd[y - 1][s][g - 2];
					RtHdHd[y - 1][s][g - 1] = RtHdHd[y - 1][s][g - 2];
				}

				TempWkWk[y][s][g] = NmWkPar[y - 1][s][g - 1] * RtWkWk[y - 1][s][g - 1];
				TempReWk[y][s][g] = NmRePar[y - 1][s][g - 1] * RtReWk[y - 1][s][g - 1];
				TempHdWk[y][s][g] = NmHdPar[y - 1][s][g - 1] * RtHdWk[y - 1][s][g - 1];

				TempWkRe[y][s][g] = NmWkPar[y - 1][s][g - 1] * RtWkRe[y - 1][s][g - 1];
				TempReRe[y][s][g] = NmRePar[y - 1][s][g - 1] * RtReRe[y - 1][s][g - 1];
				TempHdRe[y][s][g] = NmHdPar[y - 1][s][g - 1] * RtHdRe[y - 1][s][g - 1];

				TempWkHd[y][s][g] = NmWkPar[y - 1][s][g - 1] * RtWkHd[y - 1][s][g - 1];
				TempReHd[y][s][g] = NmRePar[y - 1][s][g - 1] * RtReHd[y - 1][s][g - 1];
				TempHdHd[y][s][g] = NmHdPar[y - 1][s][g - 1] * RtHdHd[y - 1][s][g - 1];

				TempNmHdPar[y][s][g] = TempWkHd[y][s][g] + TempReHd[y][s][g] + TempHdHd[y][s][g];

				NmOut[y][s][g] = (NmWkPar[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1]) * RtOut[y - 1][s][g - 1];
				NmDeath[y][s][g] = (NmWkPar[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1]) * RtDeath[y - 1][s][g - 1];
				NmAbr[y][s][g] = (NmWkPar[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1]) * RtAbr[s][g - 1];
				NmOth[y][s][g] = (NmWkPar[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1]) * RtOthIni[y - 1][s][g - 1];

				NmNpsGov[y][s][g] = (NmWkPar[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1]) * RtOthIni[y - 1][s][g - 1] * RtNpsGovIni[y - 1][s][g - 1];
				NmNpsPst[y][s][g] = (NmWkPar[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1]) * RtOthIni[y - 1][s][g - 1] * RtNpsPstIni[y - 1][s][g - 1];
				NmNpsSol[y][s][g] = (NmWkPar[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1]) * RtOthIni[y - 1][s][g - 1] * RtNpsSolIni[y - 1][s][g - 1];

				NmWkGov[y][s][g] = NmWkPar[y - 1][s][g - 1] * RtOthIni[y - 1][s][g - 1] * RtNpsGovIni[y - 1][s][g - 1];
				NmReGov[y][s][g] = NmRePar[y - 1][s][g - 1] * RtOthIni[y - 1][s][g - 1] * RtNpsGovIni[y - 1][s][g - 1];
				NmHdGov[y][s][g] = NmHdPar[y - 1][s][g - 1] * RtOthIni[y - 1][s][g - 1] * RtNpsGovIni[y - 1][s][g - 1];

				NmWkPst[y][s][g] = NmWkPar[y - 1][s][g - 1] * RtOthIni[y - 1][s][g - 1] * RtNpsPstIni[y - 1][s][g - 1];
				NmRePst[y][s][g] = NmRePar[y - 1][s][g - 1] * RtOthIni[y - 1][s][g - 1] * RtNpsPstIni[y - 1][s][g - 1];
				NmHdPst[y][s][g] = NmHdPar[y - 1][s][g - 1] * RtOthIni[y - 1][s][g - 1] * RtNpsPstIni[y - 1][s][g - 1];

				NmWkSol[y][s][g] = NmWkPar[y - 1][s][g - 1] * RtOthIni[y - 1][s][g - 1] * RtNpsSolIni[y - 1][s][g - 1];
				NmReSol[y][s][g] = NmRePar[y - 1][s][g - 1] * RtOthIni[y - 1][s][g - 1] * RtNpsSolIni[y - 1][s][g - 1];
				NmHdSol[y][s][g] = NmHdPar[y - 1][s][g - 1] * RtOthIni[y - 1][s][g - 1] * RtNpsSolIni[y - 1][s][g - 1];

				if (g <= MG)
				{
					NmHdPar[y][s][g] = NmWkPar[y - 1][s][g - 1] * RtWkHd[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] * RtReHd[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1] * RtHdHd[y - 1][s][g - 1];

					NmWkHd[y][s][g] = NmWkPar[y - 1][s][g - 1] * RtWkHd[y - 1][s][g - 1];
					NmReHd[y][s][g] = NmRePar[y - 1][s][g - 1] * RtReHd[y - 1][s][g - 1];
					NmHdHd[y][s][g] = NmHdPar[y - 1][s][g - 1] * RtHdHd[y - 1][s][g - 1];
				}
				if (g == 18)
				{
					NmWkPar[y][s][g] = TnWkPar[y][s][g];
					NmRePar[y][s][g] = TnRePar[y][s][g];
					NmNewWk[y][s][g] = TnWkPar[y][s][g];
					NmNewRe[y][s][g] = TnRePar[y][s][g];
					TempNmNewWk[y][s][g] = TnWkPar[y][s][g];
					TempNmNewRe[y][s][g] = TnRePar[y][s][g];
					NmNewWkpsm[y][s][g] = TnWkPar[y][s][g];
					NmNewRepsm[y][s][g] = TnRePar[y][s][g];
				}
				else if ((g > 18) && (g <= MG))
				{
					dtemp[1] = Pop[y - 1][s][g - 1] - (NmWkPar[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1]);
					if (dtemp[1] > 0.0)
					{
						NmNewWk[y][s][g] = dtemp[1] * RtNewWk[y][s][g];
						NmNewRe[y][s][g] = dtemp[1] * RtNewRe[y][s][g];
					}

					dtemp[1] = NmNewWk[y][s][g] + NmNewRe[y][s][g];
					dtemp[2] = TnWkPar[y][s][g] + TnRePar[y][s][g] + TempNmHdPar[y][s][g];
					dtemp[3] = Pop[y - 1][s][g - 1] - dtemp[2];

					if (dtemp[1] > dtemp[3])
					{
						if (dtemp[3] > 0.0)
						{
							NmNewWk[y][s][g] = dtemp[3] * NmNewWk[y][s][g] / dtemp[1];
							NmNewRe[y][s][g] = dtemp[3] * NmNewRe[y][s][g] / dtemp[1];
						}
						else
						{
							NmNewWk[y][s][g] = 0.0;
							NmNewRe[y][s][g] = 0.0;
						}
					}

					NmWkPar[y][s][g] = NmWkPar[y - 1][s][g - 1] * RtWkWk[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] * RtReWk[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1] * RtHdWk[y - 1][s][g - 1] + NmNewWk[y][s][g] * 1.0;

					NmWkWk[y][s][g] = NmWkPar[y - 1][s][g - 1] * RtWkWk[y - 1][s][g - 1];
					NmReWk[y][s][g] = NmRePar[y - 1][s][g - 1] * RtReWk[y - 1][s][g - 1];
					NmHdWk[y][s][g] = NmHdPar[y - 1][s][g - 1] * RtHdWk[y - 1][s][g - 1];

					NmWkRe[y][s][g] = NmWkPar[y - 1][s][g - 1] * RtWkRe[y - 1][s][g - 1];
					NmReRe[y][s][g] = NmRePar[y - 1][s][g - 1] * RtReRe[y - 1][s][g - 1];
					NmHdRe[y][s][g] = NmHdPar[y - 1][s][g - 1] * RtHdRe[y - 1][s][g - 1];

					dtemp[96] = NmWkPar[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1];
					dtemp[99] = (Pop[y - 1][s][g - 1] - NmOther[y - 1][s][g - 1] - dtemp[96]) * (1.0 - RtDeath[y - 1][s][g - 1]);

					dtemp[1] = TnWkPar[y][s][g] - NmNewWk[y][s][g] * 0.0 - NmWkPar[y][s][g];
					dtemp[11] = TempWkWk[y][s][g] + TempReWk[y][s][g] + TempHdWk[y][s][g];

					// 120번 사업장가입자 연령별 총량보다 더 많은 경우, 사업장으로 이동자는 줄이고, 대기자로 이동하는 자 증가
					if (dtemp[1] < 0.0)
					{
						NmWkWk[y][s][g] -= (-1.0) * dtemp[1] * TempWkWk[y][s][g] / dtemp[11];
						NmWkHd[y][s][g] += (-1.0) * dtemp[1] * TempWkWk[y][s][g] / dtemp[11];
						NmReWk[y][s][g] -= (-1.0) * dtemp[1] * TempReWk[y][s][g] / dtemp[11];
						NmReHd[y][s][g] += (-1.0) * dtemp[1] * TempReWk[y][s][g] / dtemp[11];
						NmHdWk[y][s][g] -= (-1.0) * dtemp[1] * TempHdWk[y][s][g] / dtemp[11];
						NmHdHd[y][s][g] += (-1.0) * dtemp[1] * TempHdWk[y][s][g] / dtemp[11];

						NmWkPar[y][s][g] -= (-1.0) * dtemp[1];
						NmHdPar[y][s][g] += (-1.0) * dtemp[1];
					}
					else if (dtemp[1] >= 0.0)
					{ // 120번 사업장 가입자 총량이 130번 계산된 것 보다 더 많은 경우
						if (NmHdPar[y][s][g] > 0.0)
						{
							if (NmHdPar[y][s][g] > dtemp[1])
							{ // 대기자가 사업장 차이보다 크면, 대기자는 줄이고 사업장은 늘리고

								NmWkHd[y][s][g] -= dtemp[1] * NmWkHd[y][s][g] / NmHdPar[y][s][g];
								NmWkWk[y][s][g] += dtemp[1] * NmWkHd[y][s][g] / NmHdPar[y][s][g];
								NmReHd[y][s][g] -= dtemp[1] * NmReHd[y][s][g] / NmHdPar[y][s][g];
								NmReWk[y][s][g] += dtemp[1] * NmReHd[y][s][g] / NmHdPar[y][s][g];
								NmHdHd[y][s][g] -= dtemp[1] * NmHdHd[y][s][g] / NmHdPar[y][s][g];
								NmHdWk[y][s][g] += dtemp[1] * NmHdHd[y][s][g] / NmHdPar[y][s][g];

								NmWkPar[y][s][g] += dtemp[1];
								NmHdPar[y][s][g] = NmWkHd[y][s][g] + NmReHd[y][s][g] + NmHdHd[y][s][g];
							}
							else if (NmHdPar[y][s][g] <= dtemp[1])
							{
								NmWkWk[y][s][g] += NmWkHd[y][s][g];
								NmWkHd[y][s][g] = 0.0;
								NmReWk[y][s][g] += NmReHd[y][s][g];
								NmReHd[y][s][g] = 0.0;
								NmHdWk[y][s][g] += NmHdHd[y][s][g];
								NmHdHd[y][s][g] = 0.0;

								NmWkPar[y][s][g] += dtemp[1];
								NmNewWk[y][s][g] += dtemp[1] - NmHdPar[y][s][g];
								TempNmNewWk[y][s][g] += dtemp[1] - NmHdPar[y][s][g];
								NmHdPar[y][s][g] = 0.0;
							}
						}
						else
						{
							NmNewWk[y][s][g] += dtemp[1];
							TempNmNewWk[y][s][g] += dtemp[1];
							NmWkPar[y][s][g] += dtemp[1];
						}
					}

					NmRePar[y][s][g] = NmWkPar[y - 1][s][g - 1] * RtWkRe[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] * RtReRe[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1] * RtHdRe[y - 1][s][g - 1] + NmNewRe[y][s][g] * 1.0;

					dtemp[2] = TnRePar[y][s][g] - NmNewRe[y][s][g] * 0.0 - NmRePar[y][s][g];
					dtemp[12] = TempWkRe[y][s][g] + TempReRe[y][s][g] + TempHdRe[y][s][g];
					dtemp[13] = NmWkHd[y][s][g] + NmReHd[y][s][g] + NmHdHd[y][s][g];

					if (dtemp[2] < 0.0)
					{
						NmWkRe[y][s][g] -= (-1.0) * dtemp[2] * TempWkRe[y][s][g] / dtemp[12];
						NmWkHd[y][s][g] += (-1.0) * dtemp[2] * TempWkRe[y][s][g] / dtemp[12];
						NmReRe[y][s][g] -= (-1.0) * dtemp[2] * TempReRe[y][s][g] / dtemp[12];
						NmReHd[y][s][g] += (-1.0) * dtemp[2] * TempReRe[y][s][g] / dtemp[12];
						NmHdRe[y][s][g] -= (-1.0) * dtemp[2] * TempHdRe[y][s][g] / dtemp[12];
						NmHdHd[y][s][g] += (-1.0) * dtemp[2] * TempHdRe[y][s][g] / dtemp[12];

						NmRePar[y][s][g] -= (-1.0) * dtemp[2];
						NmHdPar[y][s][g] += (-1.0) * dtemp[2];
					}
					else if (dtemp[2] >= 0.0)
					{
						if (dtemp[13] > 0.0)
						{
							if (dtemp[13] > dtemp[2])
							{
								NmWkHd[y][s][g] -= dtemp[2] * NmWkHd[y][s][g] / dtemp[13];
								NmWkRe[y][s][g] += dtemp[2] * NmWkHd[y][s][g] / dtemp[13];
								NmReHd[y][s][g] -= dtemp[2] * NmReHd[y][s][g] / dtemp[13];
								NmReRe[y][s][g] += dtemp[2] * NmReHd[y][s][g] / dtemp[13];
								NmHdHd[y][s][g] -= dtemp[2] * NmHdHd[y][s][g] / dtemp[13];
								NmHdRe[y][s][g] += dtemp[2] * NmHdHd[y][s][g] / dtemp[13];

								NmRePar[y][s][g] += dtemp[2];
								NmHdPar[y][s][g] -= dtemp[2];
							}
							else if (dtemp[13] < dtemp[2])
							{
								NmWkRe[y][s][g] += NmWkHd[y][s][g];
								NmWkHd[y][s][g] = 0.0;
								NmReRe[y][s][g] += NmReHd[y][s][g];
								NmReHd[y][s][g] = 0.0;
								NmHdRe[y][s][g] += NmHdHd[y][s][g];
								NmHdHd[y][s][g] = 0.0;

								NmRePar[y][s][g] += dtemp[2];
								NmNewRe[y][s][g] += dtemp[2] - NmHdPar[y][s][g];
								TempNmNewRe[y][s][g] += dtemp[2] - NmHdPar[y][s][g];
								NmHdPar[y][s][g] = 0.0;
							}
						}
						else
						{
							NmNewRe[y][s][g] += dtemp[2];
							TempNmNewRe[y][s][g] += dtemp[2];
							NmRePar[y][s][g] += dtemp[2];
						}
					}

					NmHdPar[y][s][g] = NmWkHd[y][s][g] + NmReHd[y][s][g] + NmHdHd[y][s][g];

					NmNewWkpsm[y][s][g] = NmNewWk[y][s][g];
					NmNewRepsm[y][s][g] = NmNewRe[y][s][g];

					// 연계방안 처리 시작
					if (y >= LinkYear - 1987)
					{

						// 국민연금에서 직역연금으로 이동자
						// 공무원연금 가입자
						for (e = 0; e <= E - 2; e++)
						{
							NmGov[y][s][g][e] = NmGov[y - 1][s][g - 1][e] * (1.0 - RtGovOutIni[y - 1][s][g - 1][e]);
							NmGovOut[y][s][g][e] = NmGov[y - 1][s][g - 1][e] * RtGovOutIni[y - 1][s][g - 1][e];
						}

						for (dtemp[1] = 0.0, e = 0; e <= E - 2; e++)
							dtemp[1] += NmGov[y][s][g][e];
						for (dtemp[5] = 0.0, e = 0; e <= E - 2; e++)
							dtemp[5] += NmGov[y - 1][s][g - 1][e];
						dtemp[2] = (NmWkPar[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1]) * RtOthIni[y - 1][s][g - 1] * RtNpsGovIni[y][s][g];
						dtemp[3] = TnNmGov[y][s][g] - dtemp[1];

						if (dtemp[3] >= 0.0)
						{
							if (dtemp[3] >= dtemp[2])
							{
								if (g < 60)
								{
									dtemp[4] = dtemp[3] - dtemp[2];
									NmGov[y][s][g][0] += dtemp[4];
									NmGov[y][s][g][0] += dtemp[2];
								}
								else
								{
									dtemp[4] = dtemp[3] - dtemp[2];
									for (dtemp[99] = 0.0, e = 0; e <= E - 2; e++)
										dtemp[99] += NmGov[y][s][g][e];
									if (dtemp[99] > 0.0)
									{
										for (e = 0; e <= E - 2; e++)
										{
											dtemp[98] = NmGov[y][s][g][e];
											NmGov[y][s][g][e] += dtemp[4] * dtemp[98] / dtemp[99];
											NmGovOut[y][s][g][e] -= dtemp[4] * dtemp[98] / dtemp[99];
										}
									}
									NmGov[y][s][g][0] += dtemp[2];
								}

								for (dtemp[1] = 0.0, e = 0; e <= E - 2; e++)
									dtemp[1] += NmGov[y][s][g][e];
							}
							else if (dtemp[3] < dtemp[2])
							{
								if (dtemp[2] > 0.0)
								{
									NmGov[y][s][g][0] += dtemp[3];
									dtemp[4] = NmWkGov[y][s][g] + NmReGov[y][s][g] + NmHdGov[y][s][g];
									if (dtemp[4] > 0.0)
									{
										NmWkGov[y][s][g] = dtemp[3] * NmWkGov[y][s][g] / dtemp[4];
										NmReGov[y][s][g] = dtemp[3] * NmReGov[y][s][g] / dtemp[4];
										NmHdGov[y][s][g] = dtemp[3] * NmHdGov[y][s][g] / dtemp[4];
									}
								}
								else
								{
									NmGov[y][s][g][0] += dtemp[3];
									NmWkGov[y][s][g] = 0.0;
									NmReGov[y][s][g] = 0.0;
									NmHdGov[y][s][g] = 0.0;
								}
								for (dtemp[1] = 0.0, e = 0; e <= E - 2; e++)
									dtemp[1] += NmGov[y][s][g][e];
							}
						}
						else if (dtemp[3] < 0.0)
						{
							for (dtemp[99] = 0.0, e = 0; e <= E - 2; e++)
								dtemp[99] += NmGov[y][s][g][e];
							if (dtemp[99] > 0.0)
							{
								for (e = 0; e <= E - 2; e++)
								{
									dtemp[98] = NmGov[y][s][g][e];
									NmGov[y][s][g][e] += dtemp[3] * dtemp[98] / dtemp[99];
									NmGovOut[y][s][g][e] -= dtemp[3] * dtemp[98] / dtemp[99];
								}
								NmWkGov[y][s][g] = 0.0;
								NmReGov[y][s][g] = 0.0;
								NmHdGov[y][s][g] = 0.0;
							}
							for (dtemp[1] = 0.0, e = 0; e <= E - 2; e++)
								dtemp[1] += NmGov[y][s][g][e];
						}

						for (dtemp[1] = 0.0, e = 0; e <= E - 2; e++)
							dtemp[1] += NmGov[y][s][g][e];
						dtemp[2] = NmWkGov[y][s][g] + NmReGov[y][s][g] + NmHdGov[y][s][g];
						dtemp[3] = TnNmGov[y][s][g] - dtemp[1];
						dtemp[5] = NmGov[y][s][g][0];

						for (e = 0; e <= E - 2; e++)
							NmGovNps[y][s][g][e] = NmGovOut[y][s][g][e] * RtGovOutNps[y][s][g][e];
						for (e = 0; e <= E - 2; e++)
							ftemp[e] = NmGov[y][s][g][e];
						for (e = 0; e <= E - 2; e++)
							NmGov[y][s][g][e] = 0.0;
						for (e = 0; e <= E - 2; e++)
							NmGov[y][s][g][e + 1] = ftemp[e];

						// 사학연금 가입자

						for (e = 0; e <= E - 2; e++)
						{
							NmPst[y][s][g][e] = NmPst[y - 1][s][g - 1][e] * (1.0 - RtPstOutIni[y - 1][s][g - 1][e]);
							NmPstOut[y][s][g][e] = NmPst[y - 1][s][g - 1][e] * RtPstOutIni[y - 1][s][g - 1][e];
						}

						dtemp[1] = 0.0;
						dtemp[2] = 0.0;
						dtemp[5] = 0.0;
						for (e = 0; e <= E - 2; e++)
							dtemp[1] += NmPst[y][s][g][e];
						for (e = 0; e <= E - 2; e++)
							dtemp[5] += NmPst[y - 1][s][g - 1][e];
						dtemp[2] += (NmWkPar[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1]) * RtOthIni[y - 1][s][g - 1] * RtNpsPstIni[y][s][g];
						dtemp[3] = TnNmPst[y][s][g] - dtemp[1];

						if (dtemp[3] >= 0.0)
						{
							if (dtemp[3] >= dtemp[2])
							{
								dtemp[4] = dtemp[3] - dtemp[2];
								if (s == 1)
								{
									NmPst[y][s][g][0] += dtemp[4];
									NmPst[y][s][g][0] += dtemp[2];
								}
								else if (s == 2)
								{
									NmPst[y][s][g][0] += dtemp[4];
									NmPst[y][s][g][0] += dtemp[2];
								}
								for (dtemp[1] = 0.0, e = 0; e <= E - 2; e++)
									dtemp[1] += NmPst[y][s][g][e];
							}
							else if (dtemp[3] < dtemp[2])
							{
								if (dtemp[2] > 0.0)
								{
									NmPst[y][s][g][0] += dtemp[3];
									dtemp[4] = NmWkPst[y][s][g] + NmRePst[y][s][g] + NmHdPst[y][s][g];
									if (dtemp[4] > 0.0)
									{
										NmWkPst[y][s][g] = dtemp[3] * NmWkPst[y][s][g] / dtemp[4];
										NmRePst[y][s][g] = dtemp[3] * NmRePst[y][s][g] / dtemp[4];
										NmHdPst[y][s][g] = dtemp[3] * NmHdPst[y][s][g] / dtemp[4];
									}
								}
								else
								{
									NmPst[y][s][g][0] += dtemp[3];
									NmWkPst[y][s][g] = 0.0;
									NmRePst[y][s][g] = 0.0;
									NmHdPst[y][s][g] = 0.0;
								}
								for (dtemp[1] = 0.0, e = 0; e <= E - 2; e++)
									dtemp[1] += NmPst[y][s][g][e];
							}
						}
						else if (dtemp[3] < 0.0)
						{
							for (dtemp[99] = 0.0, e = 0; e <= E - 2; e++)
								dtemp[99] += NmPst[y][s][g][e];
							if (dtemp[99] > 0.0)
							{
								for (e = 0; e <= E - 2; e++)
								{
									dtemp[98] = NmPst[y][s][g][e];
									NmPst[y][s][g][e] += dtemp[3] * dtemp[98] / dtemp[99];
									NmPstOut[y][s][g][e] -= dtemp[3] * dtemp[98] / dtemp[99];
								}
								NmWkPst[y][s][g] = 0.0;
								NmRePst[y][s][g] = 0.0;
								NmHdPst[y][s][g] = 0.0;
							}
							for (dtemp[1] = 0.0, e = 0; e <= E - 2; e++)
								dtemp[1] += NmPst[y][s][g][e];
						}

						for (dtemp[1] = 0.0, dtemp[3] = 0.0, dtemp[5] = 0.0, e = 0; e <= E - 2; e++)
						{
							dtemp[1] += NmPst[y][s][g][e];
						}
						dtemp[2] = NmWkPst[y][s][g] + NmRePst[y][s][g] + NmHdPst[y][s][g];
						dtemp[3] = TnNmPst[y][s][g] - dtemp[1];
						dtemp[5] = NmPst[y][s][g][0];

						for (e = 0; e <= E - 2; e++)
							NmPstNps[y][s][g][e] = NmPstOut[y][s][g][e] * RtPstOutNps[y][s][g][e];
						for (e = 0; e <= E - 2; e++)
							dtemp[e] = NmPst[y][s][g][e];
						for (e = 0; e <= E - 2; e++)
							NmPst[y][s][g][e] = 0.0;
						for (e = 0; e <= E - 2; e++)
							NmPst[y][s][g][e + 1] = dtemp[e];

						// 군인연금 가입자

						for (e = 0; e <= E - 2; e++)
						{
							NmSol[y][s][g][e] = NmSol[y - 1][s][g - 1][e] * (1.0 - RtSolOutIni[y - 1][s][g - 1][e]);
							NmSolOut[y][s][g][e] = NmSol[y - 1][s][g - 1][e] * RtSolOutIni[y - 1][s][g - 1][e];
						}

						dtemp[1] = 0.0;
						dtemp[2] = 0.0;
						for (e = 0; e <= E - 2; e++)
							dtemp[1] += NmSol[y][s][g][e];
						dtemp[2] = (NmWkPar[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1]) * RtOthIni[y - 1][s][g - 1] * RtNpsSolIni[y][s][g];

						dtemp[33] = 0.0;
						for (e = 0; e <= E - 2; e++)
							dtemp[33] += NmSol[y - 1][s][g - 1][e];
						dtemp[3] = TnNmSol[y][s][g] - dtemp[1];

						if (dtemp[3] >= 0.0)
						{
							if (dtemp[3] >= dtemp[2])
							{
								NmSol[y][s][g][0] += dtemp[3] - dtemp[2];
								NmSol[y][s][g][0] += dtemp[2];
								for (dtemp[1] = 0.0, e = 0; e <= E - 2; e++)
									dtemp[1] += NmSol[y][s][g][e];
							}
							else if (dtemp[3] < dtemp[2])
							{
								if (dtemp[2] > 0.0)
								{
									NmSol[y][s][g][0] += dtemp[3];
									dtemp[4] = NmWkSol[y][s][g] + NmReSol[y][s][g] + NmHdSol[y][s][g];
									if (dtemp[4] > 0.0)
									{
										NmWkSol[y][s][g] = dtemp[3] * NmWkSol[y][s][g] / dtemp[4];
										NmReSol[y][s][g] = dtemp[3] * NmReSol[y][s][g] / dtemp[4];
										NmHdSol[y][s][g] = dtemp[3] * NmHdSol[y][s][g] / dtemp[4];
									}
								}
								else
								{
									NmSol[y][s][g][0] += dtemp[3];
									NmWkSol[y][s][g] = 0.0;
									NmReSol[y][s][g] = 0.0;
									NmHdSol[y][s][g] = 0.0;
								}
								for (dtemp[1] = 0.0, e = 0; e <= E - 2; e++)
									dtemp[1] += NmSol[y][s][g][e];
							}
						}
						else if (dtemp[3] < 0.0)
						{
							for (dtemp[99] = 0.0, e = 0; e <= E - 2; e++)
								dtemp[99] += NmSol[y][s][g][e];
							if (dtemp[99] > 0.0)
							{
								for (e = 0; e <= E - 2; e++)
								{
									dtemp[98] = NmSol[y][s][g][e];
									NmSol[y][s][g][e] += dtemp[3] * dtemp[98] / dtemp[99];
									NmSolOut[y][s][g][e] -= dtemp[3] * dtemp[98] / dtemp[99];
								}
								NmWkSol[y][s][g] = 0.0;
								NmReSol[y][s][g] = 0.0;
								NmHdSol[y][s][g] = 0.0;
							}
							for (dtemp[1] = 0.0, e = 0; e <= E - 2; e++)
								dtemp[1] += NmSol[y][s][g][e];
						}

						for (dtemp[1] = 0.0, dtemp[3] = 0.0, dtemp[5] = 0.0, e = 0; e <= E - 2; e++)
						{
							dtemp[1] += NmSol[y][s][g][e];
						}
						dtemp[2] = NmWkSol[y][s][g] + NmReSol[y][s][g] + NmHdSol[y][s][g];
						dtemp[3] = TnNmSol[y][s][g] - dtemp[1];
						dtemp[5] = NmSol[y][s][g][0];

						for (e = 0; e <= E - 2; e++)
							NmSolNps[y][s][g][e] = NmSolOut[y][s][g][e] * RtSolOutNps[y][s][g][e];
						for (e = 0; e <= E - 2; e++)
							dtemp[e] = NmSol[y][s][g][e];
						for (e = 0; e <= E - 2; e++)
							NmSol[y][s][g][e] = 0.0;
						for (e = 0; e <= E - 2; e++)
							NmSol[y][s][g][e + 1] = dtemp[e];

						// 직역연금에서 국민연금으로 이동자

						for (dtemp[97] = 0.0, dtemp[98] = 0.0, dtemp[99] = 0.0, e = 0; e <= E - 2; e++)
						{
							dtemp[97] += NmGovNps[y][s][g][e];
							dtemp[98] += NmPstNps[y][s][g][e];
							dtemp[99] += NmSolNps[y][s][g][e];
						}

						for (e = 0; e <= E - 2; e++)
						{
							NmGovWk[y][s][g] += NmGovNps[y][s][g][e] * RtGovWk[y - 1][s][g - 1];
							NmPstWk[y][s][g] += NmPstNps[y][s][g][e] * RtPstWk[y - 1][s][g - 1];
							NmSolWk[y][s][g] += NmSolNps[y][s][g][e] * RtSolWk[y - 1][s][g - 1];
						}
						dtemp[96] = NmGovWk[y][s][g] + NmPstWk[y][s][g] + NmSolWk[y][s][g];

						if (dtemp[96] > 0.0)
						{
							if (NmNewWk[y][s][g] > dtemp[96])
							{
								NmNewWk[y][s][g] -= dtemp[96];
							}
							else
							{
								NmGovWk[y][s][g] = NmNewWk[y][s][g] * NmGovWk[y][s][g] / dtemp[96];
								NmPstWk[y][s][g] = NmNewWk[y][s][g] * NmPstWk[y][s][g] / dtemp[96];
								NmSolWk[y][s][g] = NmNewWk[y][s][g] * NmSolWk[y][s][g] / dtemp[96];
								NmNewWk[y][s][g] = 0.0;
							}
						}

						for (e = 0; e <= E - 2; e++)
						{
							NmGovRe[y][s][g] += NmGovNps[y][s][g][e] * RtGovRe[y - 1][s][g - 1];
							NmPstRe[y][s][g] += NmPstNps[y][s][g][e] * RtPstRe[y - 1][s][g - 1];
							NmSolRe[y][s][g] += NmSolNps[y][s][g][e] * RtSolRe[y - 1][s][g - 1];
						}
						dtemp[96] = NmGovRe[y][s][g] + NmPstRe[y][s][g] + NmSolRe[y][s][g];

						if (dtemp[96] > 0.0)
						{
							if (NmNewRe[y][s][g] > dtemp[96])
							{
								NmNewRe[y][s][g] -= dtemp[96];
							}
							else
							{
								NmGovRe[y][s][g] = NmNewRe[y][s][g] * NmGovRe[y][s][g] / dtemp[96];
								NmPstRe[y][s][g] = NmNewRe[y][s][g] * NmPstRe[y][s][g] / dtemp[96];
								NmSolRe[y][s][g] = NmNewRe[y][s][g] * NmSolRe[y][s][g] / dtemp[96];
								NmNewRe[y][s][g] = 0.0;
							}
						}

						NmGovHd[y][s][g] = dtemp[97] - NmGovWk[y][s][g] - NmGovRe[y][s][g];
						NmPstHd[y][s][g] = dtemp[98] - NmPstWk[y][s][g] - NmPstRe[y][s][g];
						NmSolHd[y][s][g] = dtemp[99] - NmSolWk[y][s][g] - NmSolRe[y][s][g];

						NmHdPar[y][s][g] += NmGovHd[y][s][g] + NmPstHd[y][s][g] + NmSolHd[y][s][g];

						if (dtemp[97] > 0.0)
						{
							RtGovWk[y][s][g - 1] = NmGovWk[y][s][g] / dtemp[97];
							RtGovRe[y][s][g - 1] = NmGovRe[y][s][g] / dtemp[97];
						}
						if (dtemp[98] > 0.0)
						{
							RtPstWk[y][s][g - 1] = NmPstWk[y][s][g] / dtemp[98];
							RtPstRe[y][s][g - 1] = NmPstRe[y][s][g] / dtemp[98];
						}
						if (dtemp[99] > 0.0)
						{
							RtSolWk[y][s][g - 1] = NmSolWk[y][s][g] / dtemp[99];
							RtSolRe[y][s][g - 1] = NmSolRe[y][s][g] / dtemp[99];
						}
					} // end if if(y>=LinkYear-1987) //

					// 연계방안 처리 종료

					// 이동률 재산정
					// From Nps

					// 5th
					if (NmWkPar[y - 1][s][g - 1] > 0.0)
					{
						if (NmWkWk[y][s][g] > 0.0)
							RtWkWk[y][s][g - 1] = NmWkWk[y][s][g] / NmWkPar[y - 1][s][g - 1];
						else if (NmWkWk[y][s][g] <= 0.0)
						{
							RtWkWk[y][s][g - 1] = RtWkWk[y - 1][s][g - 1];
						}
						if (NmWkRe[y][s][g] > 0.0)
							RtWkRe[y][s][g - 1] = NmWkRe[y][s][g] / NmWkPar[y - 1][s][g - 1];
						else if (NmWkRe[y][s][g] <= 0.0)
						{
							RtWkRe[y][s][g - 1] = RtWkRe[y - 1][s][g - 1];
						}
						if (NmWkHd[y][s][g] > 0.0)
							RtWkHd[y][s][g - 1] = NmWkHd[y][s][g] / NmWkPar[y - 1][s][g - 1];
						else if (NmWkHd[y][s][g] <= 0.0)
						{
							RtWkHd[y][s][g - 1] = RtWkHd[y - 1][s][g - 1];
						}
					}
					else
					{
						RtWkWk[y][s][g - 1] = RtWkWk[y - 1][s][g - 1];
						RtWkRe[y][s][g - 1] = RtWkRe[y - 1][s][g - 1];
						RtWkHd[y][s][g - 1] = RtWkHd[y - 1][s][g - 1];
					}

					// 5th
					if (NmRePar[y - 1][s][g - 1] > 0.0)
					{
						if (NmReWk[y][s][g] > 0.0)
							RtReWk[y][s][g - 1] = NmReWk[y][s][g] / NmRePar[y - 1][s][g - 1];
						else if (NmReWk[y][s][g] <= 0.0)
						{
							RtReWk[y][s][g - 1] = RtReWk[y - 1][s][g - 1];
						}

						if (NmReRe[y][s][g] > 0.0)
							RtReRe[y][s][g - 1] = NmReRe[y][s][g] / NmRePar[y - 1][s][g - 1];
						else if (NmReRe[y][s][g] <= 0.0)
						{
							RtReRe[y][s][g - 1] = RtReRe[y - 1][s][g - 1];
						}

						if (NmReHd[y][s][g] > 0.0)
							RtReHd[y][s][g - 1] = NmReHd[y][s][g] / NmRePar[y - 1][s][g - 1];
						else if (NmReHd[y][s][g] <= 0.0)
						{
							RtReHd[y][s][g - 1] = RtReHd[y - 1][s][g - 1];
						}
					}
					else
					{
						RtReWk[y][s][g - 1] = RtReWk[y - 1][s][g - 1];
						RtReRe[y][s][g - 1] = RtReRe[y - 1][s][g - 1];
						RtReHd[y][s][g - 1] = RtReHd[y - 1][s][g - 1];
					}

					if (NmHdPar[y - 1][s][g - 1] > 0.0)
					{
						if (NmHdWk[y][s][g] > 0.0)
							RtHdWk[y][s][g - 1] = NmHdWk[y][s][g] / NmHdPar[y - 1][s][g - 1];
						else if (NmHdWk[y][s][g] <= 0.0)
						{
							RtHdWk[y][s][g - 1] = RtHdWk[y - 1][s][g - 1];
						}
						if (NmHdRe[y][s][g] > 0.0)
							RtHdRe[y][s][g - 1] = NmHdRe[y][s][g] / NmHdPar[y - 1][s][g - 1];
						else if (NmHdRe[y][s][g] <= 0.0)
						{
							RtHdRe[y][s][g - 1] = RtHdRe[y - 1][s][g - 1];
						}

						if (NmHdHd[y][s][g] > 0.0)
							RtHdHd[y][s][g - 1] = NmHdHd[y][s][g] / NmHdPar[y - 1][s][g - 1];
						else if (NmHdHd[y][s][g] <= 0.0)
						{
							RtHdHd[y][s][g - 1] = RtHdHd[y - 1][s][g - 1];
						}
					}
					else
					{
						RtHdWk[y][s][g - 1] = RtHdWk[y - 1][s][g - 1];
						RtHdRe[y][s][g - 1] = RtHdRe[y - 1][s][g - 1];
						RtHdHd[y][s][g - 1] = RtHdHd[y - 1][s][g - 1];
					}

					RtOth[y][s][g - 1] = (NmWkGov[y][s][g] + NmWkPst[y][s][g] + NmWkSol[y][s][g] + NmReGov[y][s][g] + NmRePst[y][s][g] + NmReSol[y][s][g] + NmHdGov[y][s][g] + NmHdPst[y][s][g] + NmHdSol[y][s][g]) /
										 (NmWkPar[y - 1][s][g - 1] + NmRePar[y - 1][s][g - 1] + NmHdPar[y - 1][s][g - 1]);

					if (NmWkGov[y][s][g] + NmWkPst[y][s][g] + NmWkSol[y][s][g] + NmReGov[y][s][g] + NmRePst[y][s][g] + NmReSol[y][s][g] + NmHdGov[y][s][g] + NmHdPst[y][s][g] + NmHdSol[y][s][g] > 0.0)
					{
						RtNpsGov[y][s][g] = (NmWkGov[y][s][g] + NmReGov[y][s][g] + NmHdGov[y][s][g]) /
											(NmWkGov[y][s][g] + NmWkPst[y][s][g] + NmWkSol[y][s][g] + NmReGov[y][s][g] + NmRePst[y][s][g] + NmReSol[y][s][g] + NmHdGov[y][s][g] + NmHdPst[y][s][g] + NmHdSol[y][s][g]);

						RtNpsPst[y][s][g] = (NmWkPst[y][s][g] + NmRePst[y][s][g] + NmHdPst[y][s][g]) /
											(NmWkGov[y][s][g] + NmWkPst[y][s][g] + NmWkSol[y][s][g] + NmReGov[y][s][g] + NmRePst[y][s][g] + NmReSol[y][s][g] + NmHdGov[y][s][g] + NmHdPst[y][s][g] + NmHdSol[y][s][g]);

						RtNpsSol[y][s][g] = (NmWkSol[y][s][g] + NmReSol[y][s][g] + NmHdSol[y][s][g]) /
											(NmWkGov[y][s][g] + NmWkPst[y][s][g] + NmWkSol[y][s][g] + NmReGov[y][s][g] + NmRePst[y][s][g] + NmReSol[y][s][g] + NmHdGov[y][s][g] + NmHdPst[y][s][g] + NmHdSol[y][s][g]);
					}

					else
					{
						RtNpsGov[y][s][g] = RtNpsGov[y - 1][s][g];
						RtNpsPst[y][s][g] = RtNpsPst[y - 1][s][g];
						RtNpsSol[y][s][g] = RtNpsSol[y - 1][s][g];
					}

					// 180704 추가

					RtOut[y][s][g - 1] = RtDeath[y][s][g - 1] + RtAbr[s][g - 1] + RtOth[y][s][g - 1];

					RtWkHd[y][s][g - 1] = 1.0 - (RtWkWk[y][s][g - 1] + RtWkRe[y][s][g - 1] + RtOut[y][s][g - 1]);
					RtReHd[y][s][g - 1] = 1.0 - (RtReWk[y][s][g - 1] + RtReRe[y][s][g - 1] + RtOut[y][s][g - 1]);
					RtHdHd[y][s][g - 1] = 1.0 - (RtHdWk[y][s][g - 1] + RtHdRe[y][s][g - 1] + RtOut[y][s][g - 1]);

					// From Other
					for (e = 0; e <= E - 2; e++)
					{
						if (NmGov[y - 1][s][g - 1][e] > 0.0)
							RtGovOut[y][s][g - 1][e] = NmGovOut[y][s][g][e] / NmGov[y - 1][s][g - 1][e];
						else
							RtGovOut[y][s][g - 1][e] = RtGovOut[y - 1][s][g - 1][e];
						if (NmGovOut[y][s][g][e] > 0.0)
							RtGovOutNps[y][s][g - 1][e] = NmGovNps[y][s][g][e] / NmGovOut[y][s][g][e];
						else
							RtGovOutNps[y][s][g - 1][e] = RtGovOutNps[y - 1][s][g - 1][e];
					}
					for (e = 0; e <= E - 2; e++)
					{
						if (NmPst[y - 1][s][g - 1][e] > 0.0)
							RtPstOut[y][s][g - 1][e] = NmPstOut[y][s][g][e] / NmPst[y - 1][s][g - 1][e];
						else
							RtPstOut[y][s][g - 1][e] = RtPstOut[y - 1][s][g - 1][e];
						if (NmPstOut[y][s][g][e] > 0.0)
							RtPstOutNps[y][s][g - 1][e] = NmPstNps[y][s][g][e] / NmPstOut[y][s][g][e];
						else
							RtPstOutNps[y][s][g - 1][e] = RtPstOutNps[y - 1][s][g - 1][e];
					}
					for (e = 0; e <= E - 2; e++)
					{
						if (NmSol[y - 1][s][g - 1][e] > 0.0)
							RtSolOut[y][s][g - 1][e] = NmSolOut[y][s][g][e] / NmSol[y - 1][s][g - 1][e];
						else
							RtSolOut[y][s][g - 1][e] = RtSolOut[y - 1][s][g - 1][e];
						if (NmSolOut[y][s][g][e] > 0.0)
							RtSolOutNps[y][s][g - 1][e] = NmSolNps[y][s][g][e] / NmSolOut[y][s][g][e];
						else
							RtSolOutNps[y][s][g - 1][e] = RtSolOutNps[y - 1][s][g - 1][e];
						/**/
					}

					// 이동률 최종정리

					dtemp[1] = 0.0;
					dtemp[2] = 0.0;
					dtemp[3] = 0.0;
					dtemp[4] = 0.0;
					dtemp[5] = 0.0;
					dtemp[6] = 0.0;
					for (e = 0; e <= E - 2; e++)
					{
						dtemp[1] += NmGovNps[y][s][g][e];
						dtemp[2] += NmPstNps[y][s][g][e];
						dtemp[3] += NmSolNps[y][s][g][e];
						dtemp[4] += NmGovOut[y][s][g][e];
						dtemp[5] += NmPstOut[y][s][g][e];
						dtemp[6] += NmSolOut[y][s][g][e];
					}

					fprintf(fp501, "%4d %1d %3d %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf\n",
							y + 1987, s, g,
							RtWkWk[y][s][g - 1], RtWkRe[y][s][g - 1], RtWkHd[y][s][g - 1],
							RtReWk[y][s][g - 1], RtReRe[y][s][g - 1], RtReHd[y][s][g - 1],
							RtHdWk[y][s][g - 1], RtHdRe[y][s][g - 1], RtHdHd[y][s][g - 1],
							RtOth[y][s][g - 1], RtNpsGov[y][s][g - 1], RtNpsPst[y][s][g - 1], RtNpsSol[y][s][g - 1],
							RtGovWk[y][s][g - 1], RtGovRe[y][s][g - 1], RtPstWk[y][s][g - 1], RtPstRe[y][s][g - 1], RtSolWk[y][s][g - 1], RtSolRe[y][s][g - 1]);

					for (e = 0; e <= E - 2; e++)
					{
						fprintf(fp603, "%4d %1d %3d %2d %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf %10.6lf\n",
								y + 1987, s, g, e,
								RtGovOut[y][s][g - 1][e], RtPstOut[y][s][g - 1][e], RtSolOut[y][s][g - 1][e],
								RtGovOutNps[y][s][g][e], RtPstOutNps[y][s][g][e], RtSolOutNps[y][s][g][e]);
					}

				} // if(g<=59) end
			}
		}
	} // for(y=STARTY-1987...) end
	// 신규가입자 및 가입자 이동률 재산출 종료 //

	// 결과 출력
	for (y = 1988 - 1987; y <= ENDY - 1987; y++)
	{
		dtemp[1] = 0.0;
		dtemp[2] = 0.0;
		dtemp[3] = 0.0;
		dtemp[4] = 0.0;
		dtemp[5] = 0.0;
		dtemp[6] = 0.0;
		dtemp[7] = 0.0;
		dtemp[8] = 0.0;
		// 5th adjusted
		// for(g=18; g<=59; g++)
		for (g = 18; g <= AgeIns[y]; g++)
		{
			dtemp[1] += TnWkPar[y][1][g];
			dtemp[2] += TnWkPar[y][2][g];
			dtemp[3] += NmNewWkpsm[y][1][g];
			dtemp[4] += NmNewWkpsm[y][2][g];
			dtemp[5] += TnRePar[y][1][g];
			dtemp[6] += TnRePar[y][2][g];
			dtemp[7] += NmNewRepsm[y][1][g];
			dtemp[8] += NmNewRepsm[y][2][g];
		}
	}

	for (y = 1988 - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			// 5th adjusted
			// for(g=18; g<=59; g++)
			for (g = 18; g <= AgeIns[y]; g++)
			{
				fprintf(fp539, "%4d %1d %3d %10.2lf %10.2lf %10.2lf %10.2lf\n",
						y + 1987, s, g,
						NmNewWk[y][s][g], NmNewRe[y][s][g],
						TnWkPar[y][s][g], TnRePar[y][s][g]);
			}
		}
	}

	for (y = 1988 - 1987; y <= ENDY - 1987; y++)
	{
		dtemp[1] = 0.0;
		dtemp[2] = 0.0;
		dtemp[3] = 0.0;
		dtemp[4] = 0.0;
		dtemp[5] = 0.0;
		dtemp[6] = 0.0;
		dtemp[7] = 0.0;
		for (s = 1; s <= 2; s++)
		{
			// 5th adjusted
			// for(g=18; g<=59; g++)
			for (g = 18; g <= AgeIns[y]; g++)
			{
				dtemp[1] += Pop[y][s][g];
				dtemp[2] += NmWkPar[y][s][g];
				dtemp[3] += NmRePar[y][s][g];
				dtemp[4] += NmHdPar[y][s][g];
				for (e = 0; e <= E - 2; e++)
				{
					dtemp[5] += NmGov[y][s][g][e];
					dtemp[6] += NmPst[y][s][g][e];
					dtemp[7] += NmSol[y][s][g][e];
				}
			}
		}
	}

	for (y = 1988 - 1987; y <= ENDY - 1987; y++)
	{
		dtemp[1] = 0.0;
		dtemp[2] = 0.0;
		dtemp[3] = 0.0;
		dtemp[4] = 0.0;
		dtemp[5] = 0.0;
		dtemp[6] = 0.0;
		dtemp[7] = 0.0;
		for (s = 1; s <= 2; s++)
		{
			// 5th adjusted
			// for(g=18; g<=59; g++)
			for (g = 18; g <= AgeIns[y]; g++)
			{
				dtemp[1] += Pop[y][s][g];
				dtemp[2] += NmWkPar[y][s][g];
				dtemp[3] += NmRePar[y][s][g];
				dtemp[4] += NmHdPar[y][s][g];
			}
		}
	}

	for (y = STARTY - 1987; y <= ENDY - 1987; y++)
	{
		for (s = 1; s <= 2; s++)
		{
			// 5th adjusted
			// for(g=18; g<=59; g++)
			for (g = 18; g <= AgeIns[y]; g++)
			{
				fprintf(fp639, "%4d %1d %3d %10.6lf %10.6lf \n",
						y + 1987, s, g,
						NmNewWk[y][s][g] / TnWkPar[y][s][g], NmNewRe[y][s][g] / TnRePar[y][s][g]);
			}
		}
	}

	fclose(fp1);
	fclose(fp4);
	fclose(fp5);
	fclose(fp6);
	fclose(fp7);
	fclose(fp13);
	fclose(fp14);
	fclose(fp16);
	fclose(fp17);
	fclose(fp19);
	fclose(fp24);
	fclose(fp25);
	fclose(fp26);
	fclose(fp27);
	fclose(fp28);
	fclose(fp41);
	fclose(fp42);
	fclose(fp43);
	fclose(fp501);
	fclose(fp539);
	fclose(fp603);
	fclose(fp639);
	fclose(fp_sim);
} // main end //
