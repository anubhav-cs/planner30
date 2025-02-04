/*
Lightweight Automated Planning Toolkit
Copyright (C) 2012
Miquel Ramirez <miquel.ramirez@rmit.edu.au>
Nir Lipovetzky <nirlipo@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <bwd_action.hxx>
#include <iostream>

namespace aptk 
{
namespace backward {

Action::Action( STRIPS_Problem& p )
	: m_cost( 1 ), m_active( true )
{
	prec_set().resize( p.num_fluents() );
	add_set().resize( p.num_fluents() );
	del_set().resize( p.num_fluents() );
	edel_set().resize( p.num_fluents() );
    /** chao edit
     *
     */
	bwd_edel_set().resize(p.num_fluents());

    prec_negation_set().resize( p.num_negation_fluents() );
    add_negation_set().resize( p.num_negation_fluents() );
    del_negation_set().resize( p.num_negation_fluents() );
    edel_negation_set().resize( p.num_negation_fluents() );
    bwd_negation_edel_set().resize(p.num_negation_fluents());

}

Action::~Action()
{
}

void Action::define( const Fluent_Vec& precs, const Fluent_Vec& adds, const Fluent_Vec& dels )
{
	// define the precondition, adds and deletes
	define_fluent_list( precs, prec_vec(), prec_set() );
	define_fluent_list( adds, add_vec(), add_set() );
	define_fluent_list( dels, del_vec(), del_set() );
	define_fluent_list( dels, edel_vec(), edel_set() );
	/** chao edit
	 *
	 */
    define_fluent_list( dels, bwd_edel_vec(), bwd_edel_set() );
	
	// TODO: This should be made far more complex when mutex's are properly computed
	for ( unsigned i = 0; i < precs.size(); ++i)
	    m_prec_varval.push_back( std::make_pair(precs[i], 0) );
}

    void Action::define_negation( const Fluent_Vec& precs, const Fluent_Vec& adds, const Fluent_Vec& dels )
    {
        // define the precondition, adds and deletes
        define_fluent_list( precs, prec_negation_vec(), prec_negation_set() );
        define_fluent_list( adds, add_negation_vec(), add_negation_set() );
        define_fluent_list( dels, del_negation_vec(), del_negation_set() );
        define_fluent_list( dels, edel_negation_vec(), edel_negation_set() );
        /** chao edit
         *
         */
        define_fluent_list( dels, bwd_negation_edel_vec(), bwd_negation_edel_set() );

        // TODO: This should be made far more complex when mutex's are properly computed
        for ( unsigned i = 0; i < precs.size(); ++i)
            m_negation_prec_varval.push_back( std::make_pair(precs[i], 0) );
    }

void Action::define( const Fluent_Vec& precs, const Fluent_Vec& adds, const Fluent_Vec& dels, const Conditional_Effect_Vec& ceffs )
{
	// define the precondition, adds, deletes and conditional effects
	define( precs, adds, dels );
	m_negation_cond_effects = ceffs;
}

void Action::define_negation( const Fluent_Vec& precs, const Fluent_Vec& adds, const Fluent_Vec& dels, const Conditional_Effect_Vec& ceffs )
    {
        // define the precondition, adds, deletes and conditional effects
        define_negation( precs, adds, dels );
        m_cond_effects = ceffs;
    }


void Action::define_fluent_list(  const Fluent_Vec& in, Fluent_Vec& fluent_list, Fluent_Set& fluent_set )
{
	for ( unsigned k = 0; k < in.size(); k++ )
	{
		fluent_list.push_back( in[k] );
		fluent_set.set( in[k] );
	}
}

void	Action::print( const STRIPS_Problem& prob, std::ostream& os ) const {

	os << "Action " << signature() << std::endl;

	os << "\tPre(a) = {";
	prob.print_fluent_vec( os, prec_vec() );
	os << "}" << std::endl;
	os << "\tAdd(a) = {";
	prob.print_fluent_vec( os, add_vec() );
	os << "}" << std::endl;
	os << "\tDel(a) = {";
	prob.print_fluent_vec( os, del_vec() );
	os << "}" << std::endl;
	if( ! edel_vec().empty() ){
		os << "\teDel(a) = {";
		prob.print_fluent_vec( os, edel_vec() );
		os << "}" << std::endl;
	}
	os << "\tConditional Effects:" << std::endl;
	for ( unsigned l = 0; l < ceff_vec().size(); l++ )
	{
		os << "\t\tcond_eff " << l+1 << ":" << std::endl;
		os << "\t\tPre(cond_eff) = {";
		prob.print_fluent_vec( os, ceff_vec()[l]->prec_vec() );
		os << "}" << std::endl;
		os << "\t\tAdd(cond_eff) = {";
		prob.print_fluent_vec( os, ceff_vec()[l]->add_vec() );
		os << "}" << std::endl;
		os << "\t\tDel(cond_eff) = {";
		prob.print_fluent_vec( os, ceff_vec()[l]->del_vec() );
		os << "}" << std::endl;
	}	
	os << "Cost = " << cost() << std::endl;
}

}

}