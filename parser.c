#include "parser.h"
#include "lexerDef.h"

gitems *createNonTerminal(non_terminals nt)
{
    gitems *item = (gitems *)malloc(sizeof(gitems));
    item->isTer = false;
    item->v.non_t = nt;
    return item;
}
// Function to create and populate a gitem for terminal
gitems *createTerminal(terminals t)
{
    gitems *item = (gitems *)malloc(sizeof(gitems));
    item->isTer = true;
    item->v.t = t;
    return item;
}

void addrule(int index, non_terminals nt, int size,gitems value[]) {
    LHSNode *lhsNode;
    if(G->rules[index-1]==NULL){
    lhsNode = (LHSNode*)malloc(sizeof(LHSNode));
    lhsNode->rules=NULL;
    lhsNode->lhs = nt;
    }
    ProductionRule *currentrulehead=lhsNode->rules;
    ProductionRule *newRule = (ProductionRule*)malloc(sizeof(ProductionRule));
    newRule->head = NULL;
    newRule->next_rule = NULL;
    RHSNode* rhshead=(RHSNode *)malloc(sizeof(RHSNode));
    RHSNode*rhsptr=rhshead;
    rhshead->v=value[0].v;
    rhshead->isT=value[0].isTer;
    rhshead->next=NULL;
    for(int i = 1; i < size; i++) {
        RHSNode *rhsNode = (RHSNode *)malloc(sizeof(RHSNode));
        rhsNode->v=value[i].v;
        rhsNode->isT=value[i].isTer;
        rhsNode->next=NULL;
        rhsptr->next = rhsNode;
        rhsNode->ptr = NULL;
        rhsptr=rhsptr->next;
    }
    newRule->head=rhshead;
    if(currentrulehead==NULL){
        currentrulehead=newRule;
        lhsNode->rules=newRule;
        G->rules[index-1] = lhsNode;
        return;
    }
    if(currentrulehead->next_rule!=NULL){
        while(currentrulehead->next_rule!=NULL)
        currentrulehead=currentrulehead->next_rule;
    }
    currentrulehead->next_rule=newRule;
    
    // Add the LHSNode to the grammar
    G->rules[index-1] = lhsNode;
}
    void addGrammarRules()
{   
    gitems v1[2]={{false,otherFunctions},{false,mainFunction}};
    addrule(1, program, 2, v1);
    gitems v2[3]={{true,TK_MAIN},{false,stmts},{true,TK_END}};
    addrule(2, mainFunction, 3, v2);
    gitems v3[2]={{false,function},{false,otherFunctions}};
    addrule(3, otherFunctions, 2, v3);
    gitems v4[1] = {{true, EPS}};
    addrule(3, otherFunctions, 1, v4);

    gitems v5[6] = {{ true,TK_FUNID}, {false, input_par}, {false, output_par}, {true, TK_SEM}, {false, stmts}, {true, TK_END}};
    addrule(4, function, 6, v5);

    gitems v6[6] = {{true, TK_INPUT}, {true, TK_PARAMETER}, {true, TK_LIST}, {true, TK_SQL}, {false, parameter_list}, {true, TK_SQR}};
    addrule(5, input_par, 6, v6);

    gitems v7[6] = {{true, TK_OUTPUT}, {true, TK_PARAMETER},{true, TK_LIST}, {true, TK_SQL},{false, parameter_list}, {true, TK_SQR}};
    addrule(6, output_par, 6, v7);

    gitems v8[1] = {{true, EPS}};
    addrule(6, output_par, 1, v8);

    gitems v9[3] = {{false, dataType}, {true, TK_ID}, {false, remaining_list}};
    addrule(7, parameter_list, 3, v9);

    gitems v10[1] = {{false, primitiveDatatype}};
    addrule(8, dataType,1, v10);

    gitems v11[1] = {{false, constructedDatatype}};
    addrule(8, dataType, 1, v11);

    gitems v12[1] = {{true, TK_INT}};
    addrule(9, primitiveDatatype, 1, v12);

    gitems v13[1] = {{true, TK_REAL}};
    addrule(9, primitiveDatatype, 1, v13);

    gitems v14[2] = {{true, TK_RECORD}, {true, TK_RUID}};
    addrule(10, constructedDatatype, 2, v14);

    gitems v15[2] = {{true, TK_UNION}, {true, TK_RUID}};
    addrule(10, constructedDatatype, 2, v15);

    gitems v16[1] = {{true, TK_RUID}};
    addrule(10, constructedDatatype, 1, v16);

    gitems v19[4] = {{false, typeDefinitions}, {false,declarations}, {false,otherStmts}, {false,returnStmt}};
    addrule(12,stmts,4,v19);

    gitems v17[2] = {{true, TK_COMMA}, {false, parameter_list}};
    addrule(13, remaining_list, 2, v17);

    
    gitems v18[1] = {{true, EPS}};
    addrule( 13, remaining_list, 1 , v18);

    gitems v20[2] = {{false,typeDefinition}, {false, typeDefinitions}};
    addrule(14,typeDefinitions,2,v20);

    gitems v21[1] = {{true,EPS}};
    addrule(14,typeDefinitions, 1, v21);
    
    gitems v22[4] = {{true, TK_RECORD}, {true,TK_RUID}, {false, fieldDefinitions}, {true, TK_ENDRECORD}};
    addrule(15,typeDefinition,4,v22);

    gitems v23[4] = {{true,TK_UNION}, {true, TK_RUID}, {false, fieldDefinitions}, {true, TK_ENDUNION}};
    addrule(15,typeDefinition,4,v23);

    gitems v24[3] = {{false,fieldDefinition}, {false,fieldDefinition}, {false,moreFields}};
    addrule(16, fieldDefinitions, 3, v24);

    gitems v25[5] = {{true, TK_TYPE}, {false,fieldtype}, {true,TK_COLON}, {true,TK_FIELDID}, {true, TK_SEM}};
    addrule(17, fieldDefinition, 5, v25);

    gitems v26[1] = {{false,primitiveDatatype}};
    addrule(18,fieldtype,1,v26);

    gitems v27[1] = {{true, TK_RUID}};
    addrule(18,fieldtype,1,v27);

    gitems v28[2] = {{false,fieldDefinition}, {false, moreFields}};
    addrule(19,moreFields,2, v28);

    gitems v29[1] = {{true,EPS}};
    addrule(19,moreFields,1,v29);

    gitems v30[2] = {{false,declaration}, {false, declarations}};
    addrule(20,declarations,2,v30);

    gitems v31[1] = {{true, EPS}};
    addrule(20,declarations,1,v31);

    gitems v32[6] = {{true,TK_TYPE}, {false, dataType}, {true,TK_COLON},{true,TK_ID}, {false, global_or_not},{true, TK_SEM}};
    addrule(21, declaration, 6, v32);

    gitems v33[2] = {{true,TK_COLON}, {true, TK_GLOBAL}};
    addrule(22, global_or_not, 2, v33);

    gitems v34[1] = {{true, EPS}};
    addrule(22,global_or_not,1,v34);

    gitems v35[2] = {{false, stmt}, {false, otherStmts}};
    addrule(23,otherStmts,2,v35);

    gitems v36[1] = {{true, EPS}};
    addrule(23,otherStmts,1,v36);

    gitems v37[1] = {{false, assignmentStmt}};
    addrule(24,stmt, 1, v37);

    gitems v38[1] = {{false, iterativeStmt}};
    addrule(24, stmt, 1, v38);

    gitems v39[1] = {{false, conditionalStmt}};
    addrule(24,stmt,1,v39);

    gitems v40[1] = {{false, ioStmt}};
    addrule(24,stmt,1,v40);

    gitems v41[1] = {{false, funCallStmt}};
    addrule(24,stmt,1,v41);

    gitems v42[4] = {{false, singleOrRecId}, {true, TK_ASSIGNOP}, {false, arithmeticExpression}, {true, TK_SEM}};
    addrule(25,assignmentStmt, 4, v42);

    gitems v43[2] = {{true, TK_ID}, {false,option_single_constructed}};
    addrule(26,singleOrRecId, 2, v43);

    
    gitems v92[2] = {{false,oneExpansion}, {false,moreExpansions}};
    addrule(27,option_single_constructed, 4, v92);

    gitems v93[1] = {{true, EPS}};
    addrule(27,option_single_constructed, 2, v93);


    gitems v44[2] = {{true,TK_DOT}, {true, TK_FIELDID}};
    addrule(28,oneExpansion,2,v44);

    gitems v45[2] = {{false,oneExpansion}, {false,moreExpansions}};
    addrule(29,moreExpansions,2,v45);

    gitems v46[1] = {{true,EPS}};
    addrule(29,moreExpansions,1,v46);

    gitems v47[5] ={{true,TK_SQL}, {false,idList},{true, TK_SQR}, {true,TK_ASSIGNOP},{true,EPS}};
    addrule(31, outputParameters, 5,v47);

    gitems v95[1] ={{true,EPS}};
    addrule(31, outputParameters, 1,v95);

    gitems v48[3] = {{true, TK_SQL}, {false, idList}, {true, TK_SQR}};
    addrule(32, inputParameters, 3, v48);

    gitems v49[7] = {{true,TK_WHILE}, {true, TK_OP}, {false,booleanExpression}, {true, TK_CL}, {false, stmt}, {false,otherStmts}, {true, TK_ENDWHILE}};
    addrule(33,iterativeStmt, 7, v49);

    gitems v50[8] = {{true, TK_IF}, {false, TK_OP}, {false, booleanExpression}, {true, TK_CL}, {true, TK_THEN}, {false, stmt}, {false, otherStmts}, {false,elsePart}};
    addrule(34,conditionalStmt, 8, v50);

    gitems v51[4] = {{true, TK_ELSE}, {false, stmt}, {false, otherStmts}, {true, TK_ENDIF}};
    addrule(35,elsePart,4 ,v51);

    gitems v52[1] = {{true, TK_ENDIF}};
    addrule(35,elsePart, 1 ,v52);



    gitems v54[5] = {{true, TK_READ}, {true,TK_OP}, {false,var}, {true, TK_CL}, {true, TK_SEM}};
    addrule(36,ioStmt,5,v54);

    gitems v55[2] ={{false, term}, {false, expPrime}};
    addrule(37, arithmeticExpression, 2, v55);

    gitems v56[3] ={{false, lowPrecedenceOperators}, {false, term}, {false, expPrime}};
    addrule(38, expPrime, 3, v56);

    gitems v57[1] ={{true, EPS}};
    addrule(38, expPrime, 1, v57);

    gitems v58[2] ={{false, factor}, {false, termPrime}};
    addrule(39, term, 2, v58);

    gitems v59[3] ={{false, highPrecedenceOperators}, {false, factor}, {false, termPrime}};
    addrule(40, termPrime, 3, v59);

    gitems v60[1] ={{true, EPS}};
    addrule(40, termPrime, 2, v60);

    gitems v61[3] ={{true, TK_OP}, {false, arithmeticExpression}, {true,TK_CL}};
    addrule(41, factor, 3, v61);

    gitems v62[1] ={{false, var}};
    addrule(41, factor, 1, v62);

    gitems v63[1] ={{true, TK_MUL}};
    addrule(42, highPrecedenceOperators, 1, v63);

    gitems v64[1] ={{true, TK_DIV}};
    addrule(42, highPrecedenceOperators, 1, v64);

    gitems v65[1] ={{true, TK_PLUS}};
    addrule(43, lowPrecedenceOperators, 2, v65);

    gitems v66[1] ={{true, TK_MINUS}};
    addrule(43, lowPrecedenceOperators, 1, v66);

    gitems v67[7] ={{true, TK_OP}, {false, booleanExpression}, {true, TK_CL}, {true, TK_AND}, {true, TK_OP}, {false, booleanExpression}, {true, TK_CL}};
    addrule(44, booleanExpression, 7, v67);

    gitems v68[3] ={{false, var}, {true, relationalOp}, {false, var}};
    addrule(44, booleanExpression, 3, v68);

    gitems v69[4] ={{true, TK_NOT}, {true, TK_OP}, {false, booleanExpression}, {true, TK_CL}};
    addrule(44, booleanExpression, 4, v69);

    gitems v70[1] = {{false, singleOrRecId}};
    addrule(45, var, 1, v70);

    gitems v71[1] = {{true, TK_NUM}};
    addrule(47,var,1,v71);

    gitems v72[1] = {{true, TK_RNUM}};
    addrule(45,var,1,v72);

    gitems v73[1] = {{true, TK_AND}};
    addrule(46,logicalOp, 1, v73);

    gitems v74[1] = {{true, TK_OR}};
    addrule(46,logicalOp, 1 ,v74);

    gitems v75[1] = {{true, TK_LT}};
    addrule(47,relationalOp,1,v75);

    gitems v76[1] = {{true, TK_LE}};
    addrule(47,relationalOp, 1, v76);

    gitems v77[1] = {{true, TK_EQ}};
    addrule(47,relationalOp, 1, v77);
    
    gitems v78[1] = {{true, TK_GT}};
    addrule(47,relationalOp, 1, v78);

    gitems v79[1] = {{true, TK_GE}};
    addrule(47, relationalOp, 1, v79);

    gitems v80[1] = {{true, TK_NE}};
    addrule(47,relationalOp, 1, v80);

    gitems v81[3] = {{true, TK_RETURN}, {false, optionalReturn}, {true, TK_SEM}};
    addrule(48, returnStmt, 3, v81);

    gitems v82[3] = {{true, TK_SQL}, {false, idList}, {true, TK_SQR}};
    addrule(49, optionalReturn, 3, v82);

    gitems v83[1] = {{true, EPS}};
    addrule(49, optionalReturn, 1, v83);

    gitems v84[2] = {{true, TK_ID}, {false,more_ids}};
    addrule(50,idList, 2, v84);

    gitems v85[2] = {{true, TK_COMMA}, {false, idList}};
    addrule(51, more_ids, 2, v85);

    gitems  v86[1] = {{true, EPS}};
    addrule(51, more_ids, 1, v86);

    gitems v87[5] = {{true, TK_DEFINETYPE}, {false, A}, {true, TK_RUID}, {true, TK_AS}, {true, TK_RUID}};
    addrule(52,definetypestmt, 5, v87);

    gitems v88[1] = {{true, TK_RECORD}};
    addrule(11, A, 1, v88);

    gitems v89[1] = {{true, TK_UNION}};
    addrule(11,A,1,v89);

    gitems v90[1] = {{false,typeDefinition }};
    addrule(53, actualOrRedefined, 1, v90);

    gitems v91[1] = {{false, definetypestmt}};
    addrule(11, actualOrRedefined, 1, v91);

    gitems v94[7] = {{false, outputParameters}, {true, TK_CALL},{true, TK_FUNID}, {true, TK_WITH}, {true, TK_PARAMETERS},{false, inputParameters}, {true, TK_SEM}};
    addrule(30, funCallStmt, 7, v94);
}



void create_parse_table()
{
    PT = (ParseTable *)malloc(sizeof(ParseTable));
    if (PT == NULL)
    {
        fprintf(stderr, "Memory allocation failed for parse table.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NTC; i++)
    {
        for (int j = 0; j < TC; j++)
        {
            PT->table[i][j] = NULL;
        }
    }
}

void initiate_parse_table()
{
    for (int i = 0; i < NTC; i++)
    {
            LHSNode *current_lhs = G->rules[i];
            ProductionRule *current_rule = current_lhs->rules;
            while (current_rule != NULL)
            {   
                RHSNode *rhs_node = current_rule->head;
                if (rhs_node->isT)
                {
                    if(rhs_node->v.t==EPS){
                        terminal_node *first_terminal = first_follow_sets[rhs_node->v.non_t].follow_set->head;
                    while (first_terminal != NULL)
                    {   
                        PT->table[i][first_terminal->t] = current_rule;
                        first_terminal = first_terminal->next;
                    }
                    }
                    PT->table[i][rhs_node->v.t] = current_rule;
                }
                else
                {
                    terminal_node *first_terminal = first_follow_sets[rhs_node->v.non_t].first_set->head;
                    while (first_terminal != NULL)
                    {
                        PT->table[i][first_terminal->t] = current_rule;
                        first_terminal = first_terminal->next;
                    }
                }
                current_rule = current_rule->next_rule;
            }   
    }
}
void print_parse_table()
{
    printf("Parse Table:\n");
    printf("Non-terminals/Terminals\t");
    for (int j = 0; j < TC; j++)
    {
        printf("%d\t", j);
    }
    printf("\n");

    for (int i = 0; i < NTC; i++)
    {
        printf("%d\t", i);
        for (int j = 0; j < TC; j++)
        {
            if (PT->table[i][j] != NULL)
            {
                printf("%d\t", PT->table[i][j]); // Print the pointer value
            }
            else
            {
                printf("NULL\t");
            }
        }
        printf("\n");
    }
}

void add_terminal_tolist(terminal_list *list, terminals t)
{

    if (list->head == NULL)
    {
        list->head = (terminal_node *)malloc(sizeof(terminal_node));
        list->head->t = t;
        list->head->next = NULL;
    }
    else
    {
        terminal_node *cur = list->head;
        terminal_node *prev = NULL;

        while (cur != NULL)
        {
            if (cur->t == t)
            {
                return;
            }

            prev = cur;
            cur = cur->next;
        }

        terminal_node *newnode = (terminal_node *)malloc(sizeof(terminal_node));

        newnode->t = t;
        newnode->next = NULL;

        if (prev != NULL)
        {
            prev->next = newnode;
        }
    }
}

void join_terminal_list(terminal_list *l1, terminal_list *l2)
{
    if (l1 == NULL || l2 == NULL || l2->head == NULL)
    {
        return;
    }

    terminal_node *cur = l2->head;

    while (cur != NULL)
    {
        terminal_node *search = l1->head;
        bool found = false;

        while (search != NULL)
        {
            if (search->t == cur->t)
            {
                found = true;
                break;
            }
            search = search->next;
        }

        if (!found)
        {
            terminal_node *newnode = (terminal_node *)malloc(sizeof(terminal_node));

            if (newnode == NULL)
            {
                fprintf(stderr, "memory allocation failed\n");
                exit(EXIT_FAILURE);
            }

            newnode->t = cur->t;
            newnode->next = NULL;

            if (l1->head == NULL)
            {
                l1->head = newnode;
            }
            else
            {
                terminal_node *last = l1->head;
                while (last->next != NULL)
                {
                    last = last->next;
                }
                last->next = newnode;
            }
        }

        cur = cur->next;
    }
}

void initialise_list(terminal_list *list)
{

    if (list != NULL)
    {
        list->head = NULL;
    }
}

bool contains_epsilon(terminal_list *given_list)
{
    terminal_node *temp = given_list->head;

    while (temp != NULL)
    {
        if (temp->t == EPS)
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

void remove_epsilon(terminal_list *given_list)
{
    terminal_node *temp = given_list->head;
    terminal_node *prev = NULL;
    if (temp != NULL && temp->t == EPS)
    {
        given_list->head = temp->next;
        free(temp);
        return;
    }
    while ((temp != NULL) && (temp->next->t != EPS))
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp = NULL)
        return;
    prev->next = temp->next;
    free(temp);
    return;
}

void compute_first(non_terminals given_nt)
{

    if (first_follow_sets[given_nt].first_set == NULL)
    {
        first_follow_sets[given_nt].first_set = (terminal_list *)malloc(sizeof(terminal_list));
        initialise_list(first_follow_sets[given_nt].first_set);
    }
    ////
    else if (first_follow_sets[given_nt].first_set->head != NULL)
    {
        return;
    }

    LHSNode *lhs = G->rules[given_nt];
    for (ProductionRule *rule = lhs->rules; rule != NULL; rule = rule->next_rule)
    {
        compute_first_for_rhsnode(rule->head, first_follow_sets[given_nt].first_set);
    }
}

terminal_list *compute_first_for_rhsnode(RHSNode *rhs, terminal_list *firstset)
{

    if (rhs == NULL)
    {
        return firstset;
    }

    if (rhs->isT)
    {
        add_terminal_tolist(firstset, rhs->v.t);
    }
    else
    {
        compute_first(rhs->v.non_t);
        join_terminal_list(firstset, first_follow_sets[rhs->v.non_t].first_set);

        if (contains_epsilon(first_follow_sets[rhs->v.non_t].first_set) && rhs->next != NULL)
        {
            remove_epsilon(first_follow_sets[rhs->v.non_t].first_set);
            join_terminal_list(firstset, compute_first_for_rhsnode(rhs->next, firstset));
        }
    }
    return firstset;
}

void compute_firsts()
{
    for (int i = 0; i < NTC; i++)
    {
        compute_first(i);
    }
}

void populate_occ_follow()

{
    for (int i = 0; i < NTC; i++)
    {
        LHSNode *lhsNode = G->rules[i];
        ProductionRule *rule = lhsNode->rules;

        while (rule)
        {
            RHSNode *rhs = rule->head;

            while (rhs)
            {
                if (!rhs->isT && rhs->v.non_t != lhsNode->lhs)
                {
                    followDS *newFollow = (followDS *)malloc(sizeof(followDS));

                    if (newFollow)
                    {
                        newFollow->occurrence = rhs;
                        newFollow->parent_nt = lhsNode->lhs;
                        newFollow->next = follow_occurrence[rhs->v.non_t];
                        follow_occurrence[rhs->v.non_t] = newFollow;
                    }
                }
                rhs = rhs->next;
            }
            rule = rule->next_rule;
        }
    }
}

void find_followset(non_terminals nt)
{
    if (first_follow_sets[nt].follow_set == NULL)
    {
        first_follow_sets[nt].follow_set = (terminal_list *)malloc(sizeof(terminal_list));
        initialise_list(first_follow_sets[nt].follow_set);
    }

    else if (first_follow_sets[nt].follow_set->head != NULL)
    {
        return;
    }

    if (nt == program)
    {
        add_terminal_tolist(first_follow_sets[nt].follow_set, END_OF_INPUT);
    }

    followDS *followNode = follow_occurrence[nt];

    while (followNode)
    {
        RHSNode *occurence = followNode->occurrence;
        RHSNode *nextSymbol = occurence->next;

        if (nextSymbol)
        {
            if (nextSymbol->isT)
            {
                add_terminal_tolist(first_follow_sets[nt].follow_set, nextSymbol->v.t);
            }
            else
            {
                terminal_list *firstsetOfNext = first_follow_sets[nextSymbol->v.non_t].first_set;
                join_terminallist_exc_eps(first_follow_sets[nt].follow_set, firstsetOfNext);

                if (contains_epsilon(firstsetOfNext))
                {
                    join_terminal_list(first_follow_sets[nt].follow_set, first_follow_sets[followNode->parent_nt].follow_set);
                }
            }
        }

        else
        {
            join_terminal_list(first_follow_sets[nt].follow_set, first_follow_sets[followNode->parent_nt].follow_set);
        }

        followNode = followNode->next;
    }
}

void join_terminallist_exc_eps(terminal_list *l1, terminal_list *l2)
{
    if (l1 == NULL || l2 == NULL || l2->head == NULL)
    {
        return;
    }

    terminal_node *cur = l2->head;

    while (cur != NULL)
    {
        terminal_node *search = l1->head;
        bool found = false;

        while (search != NULL)
        {
            if ((search->t == cur->t) && (search->t != EPS))
            {
                found = true;
                break;
            }
            search = search->next;
        }

        if (!found)
        {
            terminal_node *newnode = (terminal_node *)malloc(sizeof(terminal_node));

            if (newnode == NULL)
            {
                fprintf(stderr, "memory allocation failed\n");
                exit(EXIT_FAILURE);
            }

            newnode->t = cur->t;
            newnode->next = NULL;

            if (l1->head == NULL)
            {
                l1->head = newnode;
            }
            else
            {
                terminal_node *last = l1->head;
                while (last->next != NULL)
                {
                    last = last->next;
                }
                last->next = newnode;
            }
        }
        cur = cur->next;
    }
}

void compute_follow()
{
    if (first_follow_sets[program].follow_set == NULL)
    {
        first_follow_sets[program].follow_set = (terminal_list *)malloc(sizeof(terminal_list));
        initialise_list(first_follow_sets[program].follow_set);
    }

    add_terminal_tolist(first_follow_sets[program].follow_set, END_OF_INPUT);

    populate_occ_follow();

    for (int i = 0; i < NTC; i++)
    {
        find_followset(i);
    }
}

bool createParseTree(SymbolItem *head)
{
    StackNode *startNode = (StackNode *)malloc(sizeof(StackNode));
    if (startNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed for StackNode.\n");
        exit(EXIT_FAILURE);
    }
    startNode->isT = true;
    startNode->value.non_t = END_OF_INPUT;
    startNode->next = NULL;
    StackNode *parsingStack = startNode;

    StackNode *programNode = (StackNode *)malloc(sizeof(StackNode));
    if (programNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed for StackNode\n");
        exit(EXIT_FAILURE);
    }
    programNode->isT = false;
    programNode->value.non_t = program;
    programNode->next = NULL;
    parsingStack = programNode;
    Stack->size = 1;

    treeNode *root = (treeNode *)malloc(sizeof(treeNode));
    if (root == NULL)
    {
        fprintf(stderr, "Memory allocation failed for root node.\n");
        exit(EXIT_FAILURE);
    }
    root->parent = NULL;
    root->firstChild = NULL;
    root->rightSibling = NULL;
    root->isT = false;
    root->v.non_t = program;
    treeNode *currentParent = root;
    SymbolItem *currentToken = head;

    while (parsingStack != NULL)
    {
        StackNode *top = parsingStack;
        parsingStack = parsingStack->next;

        if (top->isT && top->value.t == END_OF_INPUT)
        {
            break;
        }
        if (!top->isT)
        {
            ProductionRule *productionRule = PT->table[top->value.non_t][currentToken->token];
            if (productionRule == NULL)
            {
                fprintf(stderr, "Error: No production rule found for non-terminal '%s' and token '%s' at line %d\n",
                        non_terms[top->value.non_t], terms[currentToken->token], &(currentToken->lineCount));
                return false;
            }

            RHSNode *currentRHS = productionRule->head;
            while (currentRHS != NULL)
            {
                StackNode *rhsNode = (StackNode *)malloc(sizeof(StackNode));
                if (rhsNode == NULL)
                {
                    fprintf(stderr, "Memory allocation failed for StackNode.\n");
                    exit(EXIT_FAILURE);
                }
                rhsNode->isT = currentRHS->isT;
                rhsNode->value = currentRHS->v;
                rhsNode->next = parsingStack;
                parsingStack = rhsNode;
                currentRHS = currentRHS->next;
            }
        }
        else
        {
            if (top->value.t != currentToken->token)
            {
                fprintf(stderr, "Error: Unexpected token at '%s' at line %d\n", terms[currentToken->token], &(currentToken->lineCount));
                return false;
            }

            treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
            if (newNode = NULL)
            {
                fprintf(stderr, "Memory allocation failed for tree node.\n");
                exit(EXIT_FAILURE);
            }
            newNode->parent = currentParent;
            newNode->firstChild = NULL;
            newNode->rightSibling = NULL;
            newNode->isT = true;
            newNode->v.t = currentToken->token;
            if (currentParent->firstChild == NULL)
            {
                currentParent->firstChild = newNode;
            }
            else
            {
                treeNode *sibling = currentParent->firstChild;
                while (sibling->rightSibling != NULL)
                {
                    sibling = sibling->rightSibling;
                }
                sibling->rightSibling = newNode;
            }
            currentToken = currentToken->next;
        }
        if (parsingStack == NULL)
        {
            printf("Parsing Successful.\n");
            return true;
        }
        else
        {
            fprintf(stderr, "Error: Unexpected end of input\n");
            return false;
        }
    }
}

void printParseTree(treeNode *node, int depth)
{
    if (node == NULL)
    {
        return;
    }
    // Print current node
    printParseTree(node->firstChild, depth+1);
    for (int i = 0; i < depth; i++)
    {
        printf("  "); // Indent according to depth
    }

    if (node->isT)
    {
        printf("Terminal: %s\n", terms[node->v.t]); // define function getTokenName This function takes a token type (enumeration value) as input and returns a string representing the name or description of that token
    }
    else
    {
        printf("Non-terminal: %s\n", non_terms[node->v.non_t]);
    }

    // Print children recursively
    printParseTree(node->rightSibling, depth); // Print right sibling at same depth
}
