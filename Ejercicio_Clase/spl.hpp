/* spl.hpp.  Generated automatically by treecc */
#ifndef __yy_spl_hpp
#define __yy_spl_hpp
#line 3 "spl.tc"

	
	#include <vector>
	#include <string>
	#include <unordered_set>
	
	enum class RelationalOperator
	{
	 	LESS_EQUAL,
	 	LESS,
	 	GREATER,
	 	GREATER_EQUAL,
		EQUAL,
		NOT_EQUAL
	};
	std::string RelationalToString(RelationalOperator op);

	
	class AstNode;
	using NodeVector = std::vector<AstNode*>;
	using StdString = std::string;
	using USet = std::unordered_set<std::string>;
#line 28 "spl.hpp"

#include <new>

const int AstNode_kind = 1;
const int Program_kind = 2;
const int Statement_kind = 3;
const int Expression_kind = 6;
const int Condition_kind = 10;
const int StatementList_kind = 4;
const int AssignmentStmt_kind = 5;
const int IfStmt_kind = 9;
const int PrintStmt_kind = 13;
const int VarExpression_kind = 7;
const int NumberExpression_kind = 8;
const int RelationalExpression_kind = 11;
const int SimpleCondition_kind = 12;

class AstNode;
class Program;
class Statement;
class Expression;
class Condition;
class StatementList;
class AssignmentStmt;
class IfStmt;
class PrintStmt;
class VarExpression;
class NumberExpression;
class RelationalExpression;
class SimpleCondition;

class YYNODESTATE
{
public:

	YYNODESTATE();
	virtual ~YYNODESTATE();

#line 1 "cpp_skel.h"
private:

	struct YYNODESTATE_block *blocks__;
	struct YYNODESTATE_push *push_stack__;
	int used__;
#line 73 "spl.hpp"
private:

	static YYNODESTATE *state__;

public:

	static YYNODESTATE *getState()
		{
			if(state__) return state__;
			state__ = new YYNODESTATE();
			return state__;
		}

public:

	void *alloc(size_t);
	void dealloc(void *, size_t);
	int push();
	void pop();
	void clear();
	virtual void failed();
	virtual const char *currFilename() const;
	virtual long currLinenum() const;

};

class AstNode
{
protected:

	int kind__;
	const char *filename__;
	long linenum__;

public:

	int getKind() const { return kind__; }
	const char *getFilename() const { return filename__; }
	long getLinenum() const { return linenum__; }
	void setFilename(const char *filename) { filename__ = filename; }
	void setLinenum(long linenum) { linenum__ = linenum; }

	void *operator new(size_t);
	void operator delete(void *, size_t);

protected:

	AstNode();

public:

	virtual StdString toCpp(USet & varSet) = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~AstNode();

};

class Program : public AstNode
{
public:

	Program(AstNode * stmts);

public:

	AstNode * stmts;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~Program();

};

class Statement : public AstNode
{
protected:

	Statement();

public:

	virtual StdString toCpp(USet & varSet) = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~Statement();

};

class Expression : public AstNode
{
protected:

	Expression();

public:

	virtual StdString toCpp(USet & varSet) = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~Expression();

};

class Condition : public AstNode
{
protected:

	Condition();

public:

	virtual StdString toCpp(USet & varSet) = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~Condition();

};

class StatementList : public Statement
{
public:

	StatementList(NodeVector stmts);

public:

	NodeVector stmts;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~StatementList();

};

class AssignmentStmt : public Statement
{
public:

	AssignmentStmt(AstNode * lhs, AstNode * rhs);

public:

	AstNode * lhs;
	AstNode * rhs;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~AssignmentStmt();

};

class IfStmt : public Statement
{
public:

	IfStmt(AstNode * condition, AstNode * stmt, AstNode * elseStmt);

public:

	AstNode * condition;
	AstNode * stmt;
	AstNode * elseStmt;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~IfStmt();

};

class PrintStmt : public Statement
{
public:

	PrintStmt(AstNode * var);

public:

	AstNode * var;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~PrintStmt();

};

class VarExpression : public Expression
{
public:

	VarExpression(StdString var);

public:

	StdString var;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~VarExpression();

};

class NumberExpression : public Expression
{
public:

	NumberExpression(int number);

public:

	int number;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~NumberExpression();

};

class RelationalExpression : public Condition
{
public:

	RelationalExpression(AstNode * var1, RelationalOperator op, AstNode * var2);

public:

	AstNode * var1;
	RelationalOperator op;
	AstNode * var2;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~RelationalExpression();

};

class SimpleCondition : public Condition
{
public:

	SimpleCondition(StdString var);

public:

	StdString var;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~SimpleCondition();

};



#endif
