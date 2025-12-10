/* spl.cpp.  Generated automatically by treecc */
#line 27 "spl.tc"

	#include "spl.hpp"

	std::string RelationalToString(RelationalOperator op)
	{
		switch(op)
		{
			case RelationalOperator::LESS_EQUAL: return "<=";
		 	case RelationalOperator::LESS: return "<";
		 	case RelationalOperator::GREATER: return ">";
		 	case RelationalOperator::GREATER_EQUAL: return ">=";
			case RelationalOperator::EQUAL: return "==";
			case RelationalOperator::NOT_EQUAL: return "!=";
			default: return "UNKNOWN";
		}
	
	}


#line 23 "spl.cpp"

#include <cstddef>

#define YYNODESTATE_TRACK_LINES 1
#define YYNODESTATE_USE_ALLOCATOR 1
#line 1 "cpp_skel.cc"
/*
 * treecc node allocation routines for C++.
 *
 * Copyright (C) 2001  Southern Storm Software, Pty Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * As a special exception, when this file is copied by treecc into
 * a treecc output file, you may use that output file without restriction.
 */

#ifndef YYNODESTATE_BLKSIZ
#define	YYNODESTATE_BLKSIZ	2048
#endif

/*
 * Types used by the allocation routines.
 */
struct YYNODESTATE_block
{
	char data__[YYNODESTATE_BLKSIZ];
	struct YYNODESTATE_block *next__;

};
struct YYNODESTATE_push
{
	struct YYNODESTATE_push *next__;
	struct YYNODESTATE_block *saved_block__;
	int saved_used__;
};

/*
 * Initialize the singleton instance.
 */
#ifndef YYNODESTATE_REENTRANT
YYNODESTATE *YYNODESTATE::state__ = 0;
#endif

/*
 * Some macro magic to determine the default alignment
 * on this machine.  This will compile down to a constant.
 */
#define	YYNODESTATE_ALIGN_CHECK_TYPE(type,name)	\
	struct _YYNODESTATE_align_##name { \
		char pad; \
		type field; \
	}
#define	YYNODESTATE_ALIGN_FOR_TYPE(type)	\
	offsetof(_YYNODESTATE_align_##type, field)
#define	YYNODESTATE_ALIGN_MAX(a,b)	\
	((a) > (b) ? (a) : (b))
#define	YYNODESTATE_ALIGN_MAX3(a,b,c) \
	(YYNODESTATE_ALIGN_MAX((a), YYNODESTATE_ALIGN_MAX((b), (c))))
YYNODESTATE_ALIGN_CHECK_TYPE(int, int);
YYNODESTATE_ALIGN_CHECK_TYPE(long, long);
#if defined(WIN32) && !defined(__CYGWIN__)
YYNODESTATE_ALIGN_CHECK_TYPE(__int64, long_long);
#else
YYNODESTATE_ALIGN_CHECK_TYPE(long long, long_long);
#endif
YYNODESTATE_ALIGN_CHECK_TYPE(void *, void_p);
YYNODESTATE_ALIGN_CHECK_TYPE(float, float);
YYNODESTATE_ALIGN_CHECK_TYPE(double, double);
#define	YYNODESTATE_ALIGNMENT	\
	YYNODESTATE_ALIGN_MAX( \
			YYNODESTATE_ALIGN_MAX3	\
			(YYNODESTATE_ALIGN_FOR_TYPE(int), \
		     YYNODESTATE_ALIGN_FOR_TYPE(long), \
			 YYNODESTATE_ALIGN_FOR_TYPE(long_long)), \
  	     YYNODESTATE_ALIGN_MAX3 \
		 	(YYNODESTATE_ALIGN_FOR_TYPE(void_p), \
			 YYNODESTATE_ALIGN_FOR_TYPE(float), \
			 YYNODESTATE_ALIGN_FOR_TYPE(double)))

/*
 * Constructor for YYNODESTATE.
 */
YYNODESTATE::YYNODESTATE()
{
	/* Initialize the allocation state */
	blocks__ = 0;
	push_stack__ = 0;
	used__ = 0;

#ifndef YYNODESTATE_REENTRANT
	/* Register this object as the singleton instance */
	if(!state__)
	{
		state__ = this;
	}
#endif
}

/*
 * Destructor for YYNODESTATE.
 */
YYNODESTATE::~YYNODESTATE()
{
	/* Free all node memory */
	clear();

#ifndef YYNODESTATE_REENTRANT
	/* We are no longer the singleton instance */
	if(state__ == this)
	{
		state__ = 0;
	}
#endif
}

#ifdef YYNODESTATE_USE_ALLOCATOR

/*
 * Allocate a block of memory.
 */
void *YYNODESTATE::alloc(size_t size__)
{
	struct YYNODESTATE_block *block__;
	void *result__;

	/* Round the size to the next alignment boundary */
	size__ = (size__ + YYNODESTATE_ALIGNMENT - 1) &
				~(YYNODESTATE_ALIGNMENT - 1);

	/* Do we need to allocate a new block? */
	block__ = blocks__;
	if(!block__ || (used__ + size__) > YYNODESTATE_BLKSIZ)
	{
		if(size__ > YYNODESTATE_BLKSIZ)
		{
			/* The allocation is too big for the node pool */
			return (void *)0;
		}
		block__ = new YYNODESTATE_block;
		if(!block__)
		{
			/* The system is out of memory.  The programmer can
			   inherit the "failed" method to report the
			   out of memory state and/or abort the program */
			failed();
			return (void *)0;
		}
		block__->next__ = blocks__;
		blocks__ = block__;
		used__ = 0;
	}

	/* Allocate the memory and return it */
	result__ = (void *)(block__->data__ + used__);
	used__ += size__;
	return result__;
}

/*
 * Deallocate a block of memory.
 */
void YYNODESTATE::dealloc(void *ptr__, size_t size__)
{
	/* Nothing to do for this type of node allocator */
}

/*
 * Push the node allocation state.
 */
int YYNODESTATE::push()
{
	struct YYNODESTATE_block *saved_block__;
	int saved_used__;
	struct YYNODESTATE_push *push_item__;

	/* Save the current state of the node allocation pool */
	saved_block__ = blocks__;
	saved_used__ = used__;

	/* Allocate space for a push item */
	push_item__ = (struct YYNODESTATE_push *)
			alloc(sizeof(struct YYNODESTATE_push));
	if(!push_item__)
	{
		return 0;
	}

	/* Copy the saved information to the push item */
	push_item__->saved_block__ = saved_block__;
	push_item__->saved_used__ = saved_used__;

	/* Add the push item to the push stack */
	push_item__->next__ = push_stack__;
	push_stack__ = push_item__;
	return 1;
}

/*
 * Pop the node allocation state.
 */
void YYNODESTATE::pop()
{
	struct YYNODESTATE_push *push_item__;
	struct YYNODESTATE_block *saved_block__;
	struct YYNODESTATE_block *temp_block__;

	/* Pop the top of the push stack */
	push_item__ = push_stack__;
	if(push_item__ == 0)
	{
		saved_block__ = 0;
		used__ = 0;
	}
	else
	{
		saved_block__ = push_item__->saved_block__;
		used__ = push_item__->saved_used__;
		push_stack__ = push_item__->next__;
	}

	/* Free unnecessary blocks */
	while(blocks__ != saved_block__)
	{
		temp_block__ = blocks__;
		blocks__ = temp_block__->next__;
		delete temp_block__;
	}
}

/*
 * Clear the node allocation pool completely.
 */
void YYNODESTATE::clear()
{
	struct YYNODESTATE_block *temp_block__;
	while(blocks__ != 0)
	{
		temp_block__ = blocks__;
		blocks__ = temp_block__->next__;
		delete temp_block__;
	}
	push_stack__ = 0;
	used__ = 0;
}

#endif /* YYNODESTATE_USE_ALLOCATOR */

/*
 * Default implementation of functions which may be overridden.
 */
void YYNODESTATE::failed()
{
}

#ifdef YYNODESTATE_TRACK_LINES

const char *YYNODESTATE::currFilename() const
{
	return (const char *)0;
}

long YYNODESTATE::currLinenum() const
{
	return 0;
}

#endif
#line 304 "spl.cpp"
void *AstNode::operator new(size_t size__)
{
	return YYNODESTATE::getState()->alloc(size__);
}

void AstNode::operator delete(void *ptr__, size_t size__)
{
	YYNODESTATE::getState()->dealloc(ptr__, size__);
}

AstNode::AstNode()
{
	this->kind__ = AstNode_kind;
	this->filename__ = YYNODESTATE::getState()->currFilename();
	this->linenum__ = YYNODESTATE::getState()->currLinenum();
}

AstNode::~AstNode()
{
	// not used
}

int AstNode::isA(int kind) const
{
	if(kind == AstNode_kind)
		return 1;
	else
		return 0;
}

const char *AstNode::getKindName() const
{
	return "AstNode";
}

Program::Program(AstNode * stmts)
	: AstNode()
{
	this->kind__ = Program_kind;
	this->stmts = stmts;
}

Program::~Program()
{
	// not used
}

StdString Program::toCpp(USet & varSet)
#line 108 "spl.tc"
{
	std::string output="";
	std::string statements;

    output += "#include<iostream>\n";
    output += "#include<fstream>\n";
    output += "#include<string>\n";

    output += "int main() {\n";
	
	statements += stmts->toCpp(varSet);
	

	for(const auto &var : varSet){
		output += "int " + var + ";\n";
	}

	output += statements;

    output += "return 0;\n}";
	return output;
}
#line 376 "spl.cpp"

int Program::isA(int kind) const
{
	if(kind == Program_kind)
		return 1;
	else
		return AstNode::isA(kind);
}

const char *Program::getKindName() const
{
	return "Program";
}

Statement::Statement()
	: AstNode()
{
	this->kind__ = Statement_kind;
}

Statement::~Statement()
{
	// not used
}

int Statement::isA(int kind) const
{
	if(kind == Statement_kind)
		return 1;
	else
		return AstNode::isA(kind);
}

const char *Statement::getKindName() const
{
	return "Statement";
}

Expression::Expression()
	: AstNode()
{
	this->kind__ = Expression_kind;
}

Expression::~Expression()
{
	// not used
}

int Expression::isA(int kind) const
{
	if(kind == Expression_kind)
		return 1;
	else
		return AstNode::isA(kind);
}

const char *Expression::getKindName() const
{
	return "Expression";
}

Condition::Condition()
	: AstNode()
{
	this->kind__ = Condition_kind;
}

Condition::~Condition()
{
	// not used
}

int Condition::isA(int kind) const
{
	if(kind == Condition_kind)
		return 1;
	else
		return AstNode::isA(kind);
}

const char *Condition::getKindName() const
{
	return "Condition";
}

StatementList::StatementList(NodeVector stmts)
	: Statement()
{
	this->kind__ = StatementList_kind;
	this->stmts = stmts;
}

StatementList::~StatementList()
{
	// not used
}

StdString StatementList::toCpp(USet & varSet)
#line 131 "spl.tc"
{
	
    std::string statements;
    for(auto *stmt:stmts)
	{
		statements += stmt->toCpp(varSet) + "\n";
	}

    return statements;
}
#line 487 "spl.cpp"

int StatementList::isA(int kind) const
{
	if(kind == StatementList_kind)
		return 1;
	else
		return Statement::isA(kind);
}

const char *StatementList::getKindName() const
{
	return "StatementList";
}

AssignmentStmt::AssignmentStmt(AstNode * lhs, AstNode * rhs)
	: Statement()
{
	this->kind__ = AssignmentStmt_kind;
	this->lhs = lhs;
	this->rhs = rhs;
}

AssignmentStmt::~AssignmentStmt()
{
	// not used
}

StdString AssignmentStmt::toCpp(USet & varSet)
#line 143 "spl.tc"
{
	varSet.insert(lhs->toCpp(varSet));
	return lhs->toCpp(varSet) + "=" + rhs->toCpp(varSet) + ";";
}
#line 521 "spl.cpp"

int AssignmentStmt::isA(int kind) const
{
	if(kind == AssignmentStmt_kind)
		return 1;
	else
		return Statement::isA(kind);
}

const char *AssignmentStmt::getKindName() const
{
	return "AssignmentStmt";
}

IfStmt::IfStmt(AstNode * condition, AstNode * stmt, AstNode * elseStmt)
	: Statement()
{
	this->kind__ = IfStmt_kind;
	this->condition = condition;
	this->stmt = stmt;
	this->elseStmt = elseStmt;
}

IfStmt::~IfStmt()
{
	// not used
}

StdString IfStmt::toCpp(USet & varSet)
#line 148 "spl.tc"
{
	if(elseStmt==nullptr)
		return "if (" + condition->toCpp(varSet) + ")" + stmt->toCpp(varSet) + " ";
	else
		return "if (" + condition->toCpp(varSet) + ")" + stmt->toCpp(varSet)+ "else " +elseStmt->toCpp(varSet) + " ";
}
#line 558 "spl.cpp"

int IfStmt::isA(int kind) const
{
	if(kind == IfStmt_kind)
		return 1;
	else
		return Statement::isA(kind);
}

const char *IfStmt::getKindName() const
{
	return "IfStmt";
}

PrintStmt::PrintStmt(AstNode * var)
	: Statement()
{
	this->kind__ = PrintStmt_kind;
	this->var = var;
}

PrintStmt::~PrintStmt()
{
	// not used
}

StdString PrintStmt::toCpp(USet & varSet)
#line 167 "spl.tc"
{
    std::string output =  "std::cout << " + var->toCpp(varSet) + " << std::endl; ";
    return output;
}
#line 591 "spl.cpp"

int PrintStmt::isA(int kind) const
{
	if(kind == PrintStmt_kind)
		return 1;
	else
		return Statement::isA(kind);
}

const char *PrintStmt::getKindName() const
{
	return "PrintStmt";
}

VarExpression::VarExpression(StdString var)
	: Expression()
{
	this->kind__ = VarExpression_kind;
	this->var = var;
}

VarExpression::~VarExpression()
{
	// not used
}

StdString VarExpression::toCpp(USet & varSet)
#line 173 "spl.tc"
{
	return var; 
}
#line 623 "spl.cpp"

int VarExpression::isA(int kind) const
{
	if(kind == VarExpression_kind)
		return 1;
	else
		return Expression::isA(kind);
}

const char *VarExpression::getKindName() const
{
	return "VarExpression";
}

NumberExpression::NumberExpression(int number)
	: Expression()
{
	this->kind__ = NumberExpression_kind;
	this->number = number;
}

NumberExpression::~NumberExpression()
{
	// not used
}

StdString NumberExpression::toCpp(USet & varSet)
#line 178 "spl.tc"
{
	return std::to_string(number); 
}
#line 655 "spl.cpp"

int NumberExpression::isA(int kind) const
{
	if(kind == NumberExpression_kind)
		return 1;
	else
		return Expression::isA(kind);
}

const char *NumberExpression::getKindName() const
{
	return "NumberExpression";
}

RelationalExpression::RelationalExpression(AstNode * var1, RelationalOperator op, AstNode * var2)
	: Condition()
{
	this->kind__ = RelationalExpression_kind;
	this->var1 = var1;
	this->op = op;
	this->var2 = var2;
}

RelationalExpression::~RelationalExpression()
{
	// not used
}

StdString RelationalExpression::toCpp(USet & varSet)
#line 156 "spl.tc"
{
	return var1->toCpp(varSet) + RelationalToString(op) + var2->toCpp(varSet); 

}
#line 690 "spl.cpp"

int RelationalExpression::isA(int kind) const
{
	if(kind == RelationalExpression_kind)
		return 1;
	else
		return Condition::isA(kind);
}

const char *RelationalExpression::getKindName() const
{
	return "RelationalExpression";
}

SimpleCondition::SimpleCondition(StdString var)
	: Condition()
{
	this->kind__ = SimpleCondition_kind;
	this->var = var;
}

SimpleCondition::~SimpleCondition()
{
	// not used
}

StdString SimpleCondition::toCpp(USet & varSet)
#line 162 "spl.tc"
{ 
	return var; 
}
#line 722 "spl.cpp"

int SimpleCondition::isA(int kind) const
{
	if(kind == SimpleCondition_kind)
		return 1;
	else
		return Condition::isA(kind);
}

const char *SimpleCondition::getKindName() const
{
	return "SimpleCondition";
}

