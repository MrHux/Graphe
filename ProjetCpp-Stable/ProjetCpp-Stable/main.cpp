#pragma once
#include "stdafx.h"

int main(int argc, char* argv[])
{
	std::cout << std::endl << "Projet C++ 2 - Les Graphes - Mathieu Boutolleau & Paul Fayoux" << std::endl << std::endl;

#ifndef NDEBUG
	std::cout << "--- Beginning Unit Tests ---" << std::endl;

	printf("\n ***********************************\n");
	printf(" ** Starting Unit - Test Cedges : ** \n");
	printf(" *********************************** \n\n");

	Cedges_UNIT::TEST_UNIT_Cedges();
	Cedges_UNIT::TEST_UNIT_OperatorEqual();
	Cedges_UNIT::TEST_UNIT_OperatorEqualEqual();
	Cedges_UNIT::TEST_UNIT_OperatorNotEqual();

	printf("\n ************************************\n");
	printf(" ** Starting Unit - Test Cvertex : ** \n");
	printf(" ************************************ \n\n");

	CVertex_UNIT::TEST_UNIT_Cvertex();
	CVertex_UNIT::TEST_UNIT_VERset_list_edges_in();
	CVertex_UNIT::TEST_UNIT_VERset_list_edges_out();
	CVertex_UNIT::TEST_UNIT_VERoperatorEqual();
	CVertex_UNIT::TEST_UNIT_VERoperatorEqualEqual();
	CVertex_UNIT::TEST_UNIT_VERoperatorNotEqual();

	printf("\n ***********************************\n");
	printf(" ** Starting Unit - Test Cgraph : ** \n");
	printf(" *********************************** \n\n");

	Cgraph_UNIT::TEST_UNIT_Cgraph();
	Cgraph_UNIT::TEST_UNIT_GRAinvert_all_edges();
	Cgraph_UNIT::TEST_UNIT_GRAorder_by_degree();

	printf("\n **********************************\n");
	printf(" ** Starting Unit - Test Cfile : ** \n");
	printf(" ********************************** \n\n");

	Cfile_UNIT::TEST_UNIT_parse_file();

	printf("\n *****************************************\n");
	printf(" ** Starting Unit - Test Cgraph_table : ** \n");
	printf(" ***************************************** \n\n");

	Cgraph_table_UNIT::TEST_UNIT_Cgraph_table();
	Cgraph_table_UNIT::TEST_UNIT_GRTempty_table();
	Cgraph_table_UNIT::TEST_UNIT_GRT_delete_graph_at_index();
	Cgraph_table_UNIT::TEST_UNIT_GRT_insert_graph_at_index();
	Cgraph_table_UNIT::TEST_UNIT_GRT_replace_graph_at_index();

	printf("\n *************************************************\n");
	printf(" ** Starting Unit - Test Cmax_inde_sets_table : ** \n");
	printf(" ************************************************* \n\n");
	
	Cmax_inde_sets_table_UNIT::TEST_UNIT_Cmax_inde_sets_table_UNIT();
	Cmax_inde_sets_table_UNIT::TEST_UNIT_GRTempty_table();
	Cmax_inde_sets_table_UNIT::TEST_UNIT_MITenum_max_inde_set();

#endif

	std::cout << "--- Beginning Main Algorithm ---" << std::endl << std::endl;
	
	// Number of the operation chosen to do on run-time
	unsigned int uiChooseOperation = 0;
	unsigned int uiVerify = 1;
	clock_t ctTime_exec = 0;

	if (argc > 1 && argv[1] != NULL)
	{
		try
		{

			printf("\n *******************************************\n");
			printf(" ** Starting creation of Graph from file: ** \n");
			printf(" ******************************************* \n\n");

			std::cout << "Creating graph from file \"" << argv[1] << "\"" << std::endl;

			Cgraph * pGraph = new Cgraph(argv[1]);
			// If the graph has some vertices, print it
			if (pGraph->GRAget_nb_vertex() != 0)
			{
				pGraph->GRAprint();
			}
			// If the graph has no vertices, don't print it
			else
			{
				printf("Warning : Graph created is empty \n");
			}


		// While the choice made by the user is invalid, prompt again
		while (uiChooseOperation != 10 && uiChooseOperation!=uiVerify){
			std::cout << std::endl << "Veuiller choisir l'op\x082" << "ration \x085 faire :" << std::endl << std::endl;

			std::cout << "1 - Trouver tous les ensembles maximum ind\x082pendants de sommets version 1" << std::endl;
			std::cout << "2 - Trouver tous les ensembles maximum ind\x082pendants de sommets version 2" << std::endl;
			std::cout << "3 - Trouver tous les ensembles maximum ind\x082pendants de sommets version 3" << std::endl;
			std::cout << "4 - Trouver tous les ensembles maximum ind\x082pendants de sommets version 4" << std::endl;
			std::cout << "5 - Trouver tous les ensembles maximum ind\x082pendants de sommets version 5" << std::endl;
			std::cout << "6 - Trouver tous les ensembles maximum ind\x082pendants de sommets version 5" << std::endl;
			std::cout << "7 - Trouver un unique ensemble maximum ind\x082pendant de sommets version 7 - heuristique gloutonne" << std::endl;
			std::cout << "8 - Cr\x082" << "ation d'un graph invers\x082" << "es en argument" << std::endl;
			std::cout << "10 - Quitter" << std::endl << std::endl;

			std::cout << "Choix : ";

			// Choose operation to do, if a non number is entered, uiChooseOperation will be equals to 0
			std::cin >> uiChooseOperation;
			uiVerify = uiChooseOperation;
			if (uiChooseOperation == 0 || (uiChooseOperation>7 && uiChooseOperation!=42))
			{
				std::cout << std::endl << "\n Avertissement : votre choix est invalide." << std::endl;
			}
			// 1 - Search Independant sets
			else if (uiChooseOperation == 1){
				printf("\n ****************************************\n");
				printf(" ** Starting searching independant sets 1 : ** \n");
				printf(" **************************************** \n\n");

				Cmax_inde_sets_table * pMax_inde_sets_table = new Cmax_inde_sets_table();

				ctTime_exec = clock();

				pMax_inde_sets_table->MITenum_max_inde_set(pGraph, new Cgraph());
				std::cout << "\n\n - Ensemble maximum ind\x082" << "pendants de sommet trouv\x082" << "s : \n" << std::endl;
				ctTime_exec = clock() - ctTime_exec;
				
				pMax_inde_sets_table->GRTprint();

				std::cout << "\n\n \t\t temps d'ex\x082" << "cution " << std::endl;
				printf("%f \n\n", ((float)ctTime_exec) / CLOCKS_PER_SEC);

				std::cout << "\n\n - fin du programme - \n" << std::endl;
				uiChooseOperation = 100;
			}
			// 1 - Search Independant sets
			else if (uiChooseOperation == 2){
				printf("\n ****************************************\n");
				printf(" ** Starting searching independant sets 2 : ** \n");
				printf(" **************************************** \n\n");

				Cmax_inde_sets_table * pMax_inde_sets_table = new Cmax_inde_sets_table();

				ctTime_exec = clock();

				pMax_inde_sets_table->MITenum_max_inde_set2(pGraph, new Cgraph());
				std::cout << "\n\n - Ensemble maximum ind\x082" << "pendants de sommet trouv\x082" << "s : \n" << std::endl;
				ctTime_exec = clock() - ctTime_exec;
				
				pMax_inde_sets_table->GRTprint();

				std::cout << "\n\n \t\t temps d'ex\x082" << "cution " << std::endl;
				printf("%f \n\n", ((float)ctTime_exec) / CLOCKS_PER_SEC);

				std::cout << "\n\n - fin du programme - \n" << std::endl;
				uiChooseOperation = 100;
			}
			// 1 - Search Independant sets
			else if (uiChooseOperation == 3){
				printf("\n ****************************************\n");
				printf(" ** Starting searching independant sets 3 : ** \n");
				printf(" **************************************** \n\n");

				Cmax_inde_sets_table * pMax_inde_sets_table = new Cmax_inde_sets_table();
				ctTime_exec = clock();

				pMax_inde_sets_table->MITenum_max_inde_set3(pGraph, new Cgraph());
				std::cout << "\n\n - Ensemble maximum ind\x082" << "pendants de sommet trouv\x082" << "s : \n" << std::endl;
				ctTime_exec = clock() - ctTime_exec;

				pMax_inde_sets_table->GRTprint();
						
				std::cout << "\n\n \t\t temps d'ex\x082" << "cution " << std::endl;
				printf("%f \n\n", ((float)ctTime_exec) / CLOCKS_PER_SEC);

				std::cout << "\n\n - fin du programme - \n" << std::endl;
				uiChooseOperation = 100;
			}
			// 1 - Search Independant sets
			else if (uiChooseOperation == 4){
				printf("\n ****************************************\n");
				printf(" ** Starting searching independant sets 4 : ** \n");
				printf(" **************************************** \n\n");

				printf("TODO !!");

				/*Cmax_inde_sets_table * pMax_inde_sets_table = new Cmax_inde_sets_table();
				
				ctTime_exec = clock();

				pMax_inde_sets_table->MITenum_max_inde_set4(pGraph, new Cgraph());
				std::cout << "\n\n - Ensemble maximum ind\x082" << "pendants de sommet trouv\x082" << "s : \n" << std::endl;
				pMax_inde_sets_table->GRTprint();
				
				ctTime_exec = clock() - ctTime_exec;
				std::cout << "\n\n \t\t temps d'ex\x082" << "cution " << std::endl;
				printf("%f \n\n", ((float)ctTime_exec) / CLOCKS_PER_SEC);

				std::cout << "\n\n - fin du programme - \n" << std::endl;
				uiChooseOperation = 100;*/
			}
			// 1 - Search Independant sets
			else if (uiChooseOperation == 5){
				printf("\n ****************************************\n");
				printf(" ** Starting searching independant sets 5 : ** \n");
				printf(" **************************************** \n\n");

				Cmax_inde_sets_table * pMax_inde_sets_table = new Cmax_inde_sets_table();

				ctTime_exec = clock();

				pMax_inde_sets_table->MITenum_max_inde_set5(pGraph);
				std::cout << "\n\n - Ensemble maximum ind\x082" << "pendants de sommet trouv\x082" << "s : \n" << std::endl;
				//pMax_inde_sets_table->GRTprint();

				ctTime_exec = clock() - ctTime_exec;
				std::cout << "\n\n \t\t temps d'ex\x082" << "cution " << std::endl;
				printf("%f \n\n", ((float)ctTime_exec) / CLOCKS_PER_SEC);

				std::cout << "\n\n - fin du programme - \n" << std::endl;
				uiChooseOperation = 100;
			}

			// 6 - Search Independant sets
			else if (uiChooseOperation == 6){
				printf("\n ****************************************\n");
				printf(" ** Starting searching independant sets 6 : ** \n");
				printf(" **************************************** \n\n");

				Cmax_inde_sets_table * pMax_inde_sets_table = new Cmax_inde_sets_table();

				ctTime_exec = clock();

				pMax_inde_sets_table->MITenum_max_inde_set6(pGraph, 0);
				std::cout << "\n\n - Ensemble maximum ind\x082" << "pendants de sommet trouv\x082" << "s : \n" << std::endl;
				pMax_inde_sets_table->GRTprint();

				ctTime_exec = clock() - ctTime_exec;
				std::cout << "\n\n \t\t temps d'ex\x082" << "cution " << std::endl;
				printf("%f \n\n", ((float)ctTime_exec) / CLOCKS_PER_SEC);

				std::cout << "\n\n - fin du programme - \n" << std::endl;
				uiChooseOperation = 100;
			}
			// 7 - Search Independant sets - heuristic
			else if (uiChooseOperation == 7) {
				printf("\n ****************************************\n");
				printf(" ** Starting searching independant sets 7 : ** \n");
				printf(" **************************************** \n\n");

				Cmax_inde_sets_table * pMax_inde_sets_table = new Cmax_inde_sets_table();

				ctTime_exec = clock();

				pMax_inde_sets_table->MITenum_max_inde_set7(pGraph, 0);
				std::cout << "\n\n - Ensemble maximum ind\x082" << "pendant de sommet trouv\x082" << " : \n" << std::endl;
				pMax_inde_sets_table->GRTprint();

				ctTime_exec = clock() - ctTime_exec;
				std::cout << "\n\n \t\t temps d'ex\x082" << "cution " << std::endl;
				printf("%f \n\n", ((float)ctTime_exec) / CLOCKS_PER_SEC);

				std::cout << "\n\n - fin du programme - \n" << std::endl;
				uiChooseOperation = 100;
			}
			// 2 - Invert graph
			else if (uiChooseOperation == 8)
			{
				printf("\n ****************************************\n");
				printf(" ** Starting creation inverted graph 8 : ** \n");
				printf(" **************************************** \n\n");

				Cgraph * pInvertedGraph = pGraph->GRAinvert_all_edges();
				// If the graph has some vertices, invert it
				if (pGraph->GRAget_nb_vertex() != 0)
				{
					pInvertedGraph->GRAprint();
				}
				// If the graph has no vertices, don't invert it
				else
				{
					printf("Warning : No graph to invert, the program will stop. \n");
				}
				uiChooseOperation = 100;
			}
			// 3 - Quit
			else if (uiChooseOperation == 10){
				uiChooseOperation = 100;
				break;
			}
			else if (uiChooseOperation == 42){
				uiChooseOperation = 100;
				std::cout << "\n Ceci n'est pas un oeuf de p\x083" << "cques ! " << std::endl;
			}
		}


		}
		catch (Cexception exc)
		{
			printf("Exception risen , code : %d ", exc.EXCgetValue());
			switch (exc.EXCgetValue())
			{
			default: 
			case	ERROR_INDEX_OUT_OF_BOUND :
				printf("(ERROR_INDEX_OUT_OF_BOUND)");
				break;
			case	ERROR_NULL_POINTER:
				printf("(ERROR_NULL_POINTER)");
				break;
			case	ERROR_UNEXPECTED_TOKEN_READ:
				printf("(ERROR_UNEXPECTED_TOKEN_READ)");
				break;
			case	ERROR_NULL_LIST_NB_ELEMENT_NOT_NULL:
				printf("ERROR_NULL_LIST_NB_ELEMENT_NOT_NULL)");
				break;
			case	ERROR_DIFFERENTS_SIZE_IN_PARAMS:
				printf("(ERROR_DIFFERENTS_SIZE_IN_PARAMS)");
				break;
			case	ERROR_LIST_NOT_NULL:
				printf("(ERROR_LIST_NOT_NULL)");
				break;
			case	ERROR_INPUT_FILE_OPEN:
				printf("(ERROR_INPUT_FILE_OPEN)");
				break;
			case	ERROR_CHANGING_SIZE_TABLE_VALUES:
				printf("(ERROR_CHANGING_SIZE_TABLE_VALUES)");
				break;
			case	ERROR_REALLOCATION_MEMORY:
				printf("(ERROR_REALLOCATION_MEMORY)");
				break;
			}
		}
		std::cout << std::endl;
	}
	else
	{
		printf("Warning : No valid argument, the program will stop.");
	}
	return 0;

}

