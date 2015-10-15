#include "stdafx.h"

/***
* Cmax_inde_sets_table() - create a new Cmax_inde_sets_table with null value
*
*Purpose:
*       create a new Cmax_inde_sets_table with null value
*
*Entry:
*       none
*
*Return:
*		nothing
*
*******************************************************************************/
Cmax_inde_sets_table::Cmax_inde_sets_table()
{
	this->uiMITsize_max = 0;
}

/***
* ~Cmax_inde_sets_table() - delete correctly a Cmax_inde_sets_table object
*
*Purpose:
*       delete a Cmax_inde_sets_table object , it remove all independant set in the list a free the object
*
*Entry:
*       none
*
*Return:
*		nothing
*
*******************************************************************************/
Cmax_inde_sets_table::~Cmax_inde_sets_table()
{
	GRTempty_table();
}

/***
* unsigned int MITget_size_max()	-	get the maximum size of the independant set
*
*Purpose:
*       get the maximum size of the independant set of the list.
*
*Entry:
*       none
*
*Return:
*		unsigned int	-	the maximum size of the independant set
*
*******************************************************************************/
unsigned int Cmax_inde_sets_table::MITget_size_max(){
	return uiMITsize_max;
}

/***
* void GRTempty_table() - empty the table of independant sets
*
*Purpose:
*       delete all the independant sets inside the table, and set the uiMITsize_max to 0
*
*Entry:
*       none
*
*Return:
*		nothing
*
*******************************************************************************/
void Cmax_inde_sets_table::GRTempty_table(){
	Cgraph_table::GRTempty_table();
	this->uiMITsize_max = 0;
}


/***
* void MITenum_max_inde_set(Cgraph * pGraph, Cgraph * pIndependant_sets) - search all the maximum independant sets of a graph
*
*Purpose:
*       search all the maximum independant sets of a graph
*
*Entry:
*       Cgraph * pGraph				-		a graph , to determine independant sets
*		Cgraph * pIndependant_sets	-		an independant set of the graph, NULL if first call of the function.
*
*Return:
*		nothing
*
*******************************************************************************/
void Cmax_inde_sets_table::MITenum_max_inde_set(Cgraph * pGraph, Cgraph * pIndependant_sets){
	Cgraph * pGraph_copy = new Cgraph(*pGraph);
	if (pGraph_copy->GRAget_nb_vertex() == 0){
		if (pIndependant_sets->GRAget_nb_vertex() > uiMITsize_max){
			this->GRTempty_table();
			this->GRTadd_graph(pIndependant_sets);
			this->uiMITsize_max = pIndependant_sets->GRAget_nb_vertex();
		}
		else if (pIndependant_sets->GRAget_nb_vertex() == this->uiMITsize_max){
			this->GRTadd_graph(pIndependant_sets);
		}
	}
	else{
		/*browse the graph with index (position of vertex in the table) , index are different of vertex id
		* vertex of index 1 is the first vertex in the table
		*/
		for (unsigned int uiIndex_vertex = 0; uiIndex_vertex < pGraph_copy->GRAget_nb_vertex(); uiIndex_vertex++){
			
			Cvertex * pVertex = pGraph_copy->GRAget_vertex(uiIndex_vertex);// get the vertex at index
			unsigned int uiVertex_id = pVertex->VERget_id_vertex();//get the id of the vertex
			pIndependant_sets->GRAadd_vertex(new Cvertex(*pVertex));//add a copy of the vertex to the independant set
			//remove all vertex who has a shared edge
			pGraph_copy->GRAdelete_vertex_pointed_by(uiVertex_id);
			pGraph_copy->GRAdelete_vertex_who_point(uiVertex_id);
			pGraph_copy->GRAremove_vertex_from_vertex_id(uiVertex_id);//remove the vertex
			MITenum_max_inde_set(pGraph_copy, pIndependant_sets);//call the function on this new graph
			delete(pGraph_copy);//delete old copy who lack some vertices
			pIndependant_sets = new Cgraph();
			pGraph_copy = new Cgraph(*pGraph);//get a new copy with all vertices
		}
	}
}

/***
* void MITenum_max_inde_set(Cgraph * pGraph, Cgraph * pIndependant_sets) - search all the maximum independant sets of a graph
*
*Purpose:
*       search all the maximum independant sets of a graph
*		This method begin to search a solution by taking the vertex who as the less edges.
*
*Entry:
*       Cgraph * pGraph				-		a graph , to determine independant sets
*		Cgraph * pIndependant_sets	-		an independant set of the graph, NULL if first call of the function.
*
*Return:
*		nothing
*
*******************************************************************************/
void Cmax_inde_sets_table::MITenum_max_inde_set2(Cgraph * pGraph, Cgraph * pIndependant_sets){
	printf("TODO");
}


/***
* void MITenum_max_inde_set(Cgraph * pGraph, Cgraph * pIndependant_sets) - search all the maximum independant sets of a graph
*
*Purpose:
*       search all the maximum independant sets of a graph
*
*Entry:
*       Cgraph * pGraph				-		a graph , to determine independant sets
*		Cgraph * pIndependant_sets	-		an independant set of the graph, NULL if first call of the function.
*
*Return:
*		nothing
*
*******************************************************************************/
void Cmax_inde_sets_table::MITenum_max_inde_set3(Cgraph * pGraph, Cgraph * pIndependant_sets){
	Cgraph * pGraph_copy = new Cgraph(*pGraph);
	pGraph_copy->GRAorder_by_degree();
	Cgraph * pCopy_independant_sets = new Cgraph(*pIndependant_sets);

	/*
	printf("\n\n \t\t Affichage du graphe entrée dans la fonction : nb vertex %d", pGraph_copy->GRAget_nb_vertex());
	pGraph_copy->GRAprint();
	*/

	if (pGraph_copy->GRAget_nb_vertex() == 0){
		if (pIndependant_sets->GRAget_nb_vertex() > uiMITsize_max){
			this->GRTempty_table();
			this->GRTadd_graph(pIndependant_sets);
			this->uiMITsize_max = pIndependant_sets->GRAget_nb_vertex();
		}
		else if (pIndependant_sets->GRAget_nb_vertex() == this->uiMITsize_max){
			pIndependant_sets->GRAorder_by_id();
			bool bSolution_exist = this->MITtest_if_solution_exist(pIndependant_sets);
			if (bSolution_exist == false){
				this->GRTadd_graph(pIndependant_sets);
			}
		}
	}
	else{
		unsigned int uiMin_nb_edges = (pGraph_copy->GRAget_vertex(0)->VERget_nb_edges_out() + pGraph_copy->GRAget_vertex(0)->VERget_nb_edges_in());
		unsigned int uiCurrent_nb_edges = uiMin_nb_edges;


		/*browse the graph with index (position of vertex in the table) , index are different of vertex id
		* vertex of index 1 is the first vertex in the table
		*/
		for (unsigned int uiIndex_vertex = 0; uiIndex_vertex < pGraph_copy->GRAget_nb_vertex() ; uiIndex_vertex++){

			uiCurrent_nb_edges = (pGraph_copy->GRAget_vertex(uiIndex_vertex)->VERget_nb_edges_out() + pGraph_copy->GRAget_vertex(uiIndex_vertex)->VERget_nb_edges_in());

			if (uiCurrent_nb_edges <= uiMin_nb_edges +1){

				Cvertex * pVertex = pGraph_copy->GRAget_vertex(uiIndex_vertex);// get the vertex at index
				unsigned int uiVertex_id = pVertex->VERget_id_vertex();//get the id of the vertex
				pCopy_independant_sets->GRAadd_vertex(new Cvertex(*pVertex));//add a copy of the vertex to the independant set
				//remove all vertex who has a shared edge
				pGraph_copy->GRAdelete_vertex_pointed_by(uiVertex_id);
				pGraph_copy->GRAdelete_vertex_who_point(uiVertex_id);
				pGraph_copy->GRAremove_vertex_from_vertex_id(uiVertex_id);//remove the vertex
				MITenum_max_inde_set3(pGraph_copy, pCopy_independant_sets);//call the function on this new graph
				delete(pGraph_copy);//delete old copy who lack some vertices
				pCopy_independant_sets = new Cgraph(*pIndependant_sets);//get a new copy of the current independent set to be calculated
				pGraph_copy = new Cgraph(*pGraph);//get a new copy with all vertices
				pGraph_copy->GRAorder_by_degree();

			}

		}
	}
}

/***
* void MITenum_max_inde_set(Cgraph * pGraph, Cgraph * pIndependant_sets) - search all the maximum independant sets of a graph
*
*Purpose:
*       search all the maximum independant sets of a graph
*
*Entry:
*       Cgraph * pGraph				-		a graph , to determine independant sets
*		Cgraph * pIndependant_sets	-		an independant set of the graph, NULL if first call of the function.
*
*Return:
*		nothing
*
*******************************************************************************/
void Cmax_inde_sets_table::MITenum_max_inde_set4(Cgraph * pGraph, Cgraph * pIndependant_sets){
	Cgraph * pGraph_copy = new Cgraph(*pGraph);
	pGraph_copy->GRAorder_by_degree();

	/*
	printf("\n\n \t\t Affichage du graphe entrée dans la fonction : nb vertex %d", pGraph_copy->GRAget_nb_vertex());
	pGraph_copy->GRAprint();
	*/

	if (pGraph_copy->GRAget_nb_vertex() == 0){
		if (pIndependant_sets->GRAget_nb_vertex() > uiMITsize_max){
			this->GRTempty_table();
			this->GRTadd_graph(pIndependant_sets);
			this->uiMITsize_max = pIndependant_sets->GRAget_nb_vertex();
		}
		else if (pIndependant_sets->GRAget_nb_vertex() == this->uiMITsize_max){
			this->GRTadd_graph(pIndependant_sets);
		}
	}
	else{
		unsigned int uiMin_nb_edges = (pGraph_copy->GRAget_vertex(0)->VERget_nb_edges_out() + pGraph_copy->GRAget_vertex(0)->VERget_nb_edges_in());
		unsigned int uiCurrent_nb_edges = uiMin_nb_edges;
		unsigned int uiNb_edges_of_successors = 0;
		if (uiMin_nb_edges == 0) uiMin_nb_edges = 1;
		uiNb_edges_of_successors = pGraph_copy->GRAcount_nb_edge_of_successor(0) / uiMin_nb_edges ;
		unsigned int uiMax_nb_edge_of_successors = pGraph_copy->GRAget_max_nb_edge_of_successor();




		/*browse the graph with index (position of vertex in the table) , index are different of vertex id
		* vertex of index 1 is the first vertex in the table
		* because our representation an unoriented edge is equal of 2 edges so the number 4 corespond to 2 egdes 
		*/
		for (unsigned int uiIndex_vertex = 0; uiIndex_vertex < pGraph_copy->GRAget_nb_vertex() && uiCurrent_nb_edges <= uiMin_nb_edges + 4 ; uiIndex_vertex++){

			if (uiNb_edges_of_successors >= uiMax_nb_edge_of_successors - uiMax_nb_edge_of_successors + 1|| uiNb_edges_of_successors == 0){

				Cvertex * pVertex = pGraph_copy->GRAget_vertex(uiIndex_vertex);// get the vertex at index
				unsigned int uiVertex_id = pVertex->VERget_id_vertex();//get the id of the vertex
				pIndependant_sets->GRAadd_vertex(new Cvertex(*pVertex));//add a copy of the vertex to the independant set
				//remove all vertex who has a shared edge
				pGraph_copy->GRAdelete_vertex_pointed_by(uiVertex_id);
				pGraph_copy->GRAdelete_vertex_who_point(uiVertex_id);
				pGraph_copy->GRAremove_vertex_from_vertex_id(uiVertex_id);//remove the vertex
				MITenum_max_inde_set4(pGraph_copy, pIndependant_sets);//call the function on this new graph
				delete(pGraph_copy);//delete old copy who lack some vertices
				pIndependant_sets->GRAremove_vertex_from_vertex_id(uiVertex_id);//remove the last vertex added 
				pGraph_copy = new Cgraph(*pGraph);//get a new copy with all vertices
				pGraph_copy->GRAorder_by_degree();

				/*
				printf("\n\n \t\t Affichage du graphe fin de boucle : nb vertex %d", pGraph_copy->GRAget_nb_vertex());
				pGraph_copy->GRAprint();
				*/

			}

			//calcul of the nb of edge of the next vertex
			if (uiIndex_vertex < pGraph_copy->GRAget_nb_vertex() - 1){
				uiCurrent_nb_edges = (pGraph_copy->GRAget_vertex(uiIndex_vertex + 1)->VERget_nb_edges_out() + pGraph_copy->GRAget_vertex(uiIndex_vertex + 1)->VERget_nb_edges_in());
			}
			if (uiCurrent_nb_edges == 0)uiCurrent_nb_edges = 1;
			uiNb_edges_of_successors = pGraph_copy->GRAcount_nb_edge_of_successor(uiIndex_vertex) / uiCurrent_nb_edges;
			

		}
	}
}

/***
* void MITenum_max_inde_set(Cgraph * pGraph, Cgraph * pIndependant_sets) - search all the maximum independant sets of a graph
*
*Purpose:
*       search all the maximum independant sets of a graph
*
*Entry:
*       Cgraph * pGraph				-		a graph , to determine independant sets
*		Cgraph * pIndependant_sets	-		an independant set of the graph, NULL if first call of the function.
*
*Return:
*		nothing
*
*******************************************************************************/
void Cmax_inde_sets_table::MITenum_max_inde_set5(Cgraph * pGraph, Cgraph * pIndependant_sets){
	printf("TODO");
}


bool Cmax_inde_sets_table::MITtest_if_solution_exist(Cgraph * pGraph_to_compare){

	pGraph_to_compare->GRAorder_by_id();

	bool bSolution_exist = false;
	for (unsigned int uiIndex_solution = 0; uiIndex_solution < this->GRTget_nb_graph(); uiIndex_solution++){

		this->GRTget_graph(uiIndex_solution)->GRAorder_by_id();
		if (this->GRTget_graph(uiIndex_solution) == NULL && pGraph_to_compare == NULL){
			return true;//if both pointer are null they are equal
		}
		else if (this->GRTget_graph(uiIndex_solution) == NULL || pGraph_to_compare == NULL){
			bSolution_exist = false;//if one pointer is null and other one not , they are different
		}
		else{
			//test if number of vertex are the same
			if (pGraph_to_compare->GRAget_nb_vertex() == uiMITsize_max){
				//compare pointer on vertex list if the pointer are the same the graph are equal (but that should not appear)
				if (pGraph_to_compare->GRAget_vertices() == this->GRTget_graph(uiIndex_solution)->GRAget_vertices()){
					return true;
				}
				else{
					bSolution_exist = true;//the vertex list are the same in both graph so they are equal
					//test if content of vertex list are the same 
					for (unsigned int uiIndexVertex = 0; uiIndexVertex < uiMITsize_max; uiIndexVertex++){
						if (this->GRTget_graph(uiIndex_solution)->GRAget_vertex(uiIndexVertex)->VERget_id_vertex() != pGraph_to_compare->GRAget_vertex(uiIndexVertex)->VERget_id_vertex()){
							bSolution_exist = false;//one element is different so they are not equal
						}
					}
				}
			}
			else{
				bSolution_exist = false;//if number of vertex are not the same
			}
		}
		if (bSolution_exist == true) return true;
	}

	return bSolution_exist;

}