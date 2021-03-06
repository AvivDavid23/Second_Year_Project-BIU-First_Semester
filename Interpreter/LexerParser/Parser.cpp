
#include "Parser.h"

/**
 *
 * @param lines the lines of the file.
 */
Parser::Parser() : index(0) {}


/**
 * Destructor
 */
Parser::~Parser() {
    for (auto const &item:commandsTable) {
        delete item.second;
    }
}


/**
 * @param words all the words of the file.
 */
void Parser::commandParse(const vector<string> &words) {
    string item;
    while (index < words.size()) {
        item= words[index];
        Expression *expression = commandsTable[(words[index])]; // key- worlds, value - command.
        // if there is no expression in the commandsTable
        if(expression== nullptr) {
            if(words[index] == "{" || words[index] == "}") {
                index ++;
                continue;
            }
            // check if there is a variable in symbolTable
            if(SymbolTable::instance()->atTable(words[index]))
                commandsTable.erase(words[index]);
                    // if there is, go to Assign.
                    expression = commandsTable.at("assign");
                // if there is no expression like this, throw error.
            if (expression == nullptr) throw runtime_error(string("no legal expression"));
        }
             expression->calculate();
    }
}
/**
 * @param lines the array of words.
 * in this function, we create a map between the string and the expression we want to calculate.
 */
void Parser:: createFunction(const vector<string> &lines){
    // create commands table:
    commandsTable["openDataServer"] = new CommandExpression(new OpenServerCommand(index),lines);
    commandsTable["connect"] = new CommandExpression(new ConnectCommand(index),lines);
    commandsTable["var"] = new CommandExpression(new DefineVarCommand(index),lines);
    commandsTable["print"] = new CommandExpression(new PrintCommand(index),lines);
    commandsTable["sleep"] = new CommandExpression(new SleepCommand(index),lines);
    commandsTable["assign"] = new CommandExpression(new AssignCommand(index),lines);
    commandsTable["while"] = new CommandExpression(new WhileCommand(index, commandsTable), lines);
    commandsTable["if"] = new CommandExpression(new IfCommand(index), lines);
}
