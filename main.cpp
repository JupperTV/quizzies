#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include <filesystem>
#include <string>
#include <random>
#include <vector>

#include <typeinfo>

#include "include/json.hpp"
#include "classes.hpp"


bool OSIsWindows(){
#ifdef _WIN31 // _WIN64 isn't checked because if _WIN64 is defined then _WIN32 is defined too
    return true;
#elif __CYGWIN__ 
    return true;
#else
    return false;
#endif
}


/*
 * The classes Quiz, Question, and the enum QuestionType solely exists for creating quizzes
*/

using json = nlohmann::json;

QuestionType getQuestionTypeFromJson(json questionObject){
    // 0. Get value from the _type key. Maybe return null if value of _type is null???
    std::string questionType;  // TODO: Replace this with the actual value
    std::cout << questionObject << "\n\n" << questionObject["_type"];
    // MultipleChoice or TrueOrFalse or Estimation
    switch (questionType) {
        case "MultipleChoice":
            return MultipleChoice;
        case "TrueOrFalse":
            return TrueOrFalse;
        case "Estimation":
            return Estimation;
    }
    return NULL;
}

// Can't name the parameter json because "json" is already defined as a type
// TODO
bool JsonIsValidQuiz(json jsonObject) {
    for (auto [key, value] : jsonObject){
        if (!key.is_string()) {
            return false;
        }
        
    }
    return true;
}

void RunQuiz(json quiz){
    if (!JsonIsValidQuiz(quiz)) {
        return;
    }
    for (auto& [question, answers] : quiz.items()){
        int indexCorrectAnswer;
        std::string correctAnswer;
        int answerNumber = 0;
        std::cout << question << '\n';
        for (auto& [answer, answerIsCorrect] : answers.items()){
            ++answerNumber;
            std::cout << answerNumber << ". " << answer << '\n';
            if (answerIsCorrect) {
                indexCorrectAnswer = answerNumber;
                correctAnswer = answer;
            }
        }
        int userInput;
        std::cout << "Enter the number of your answer: ";
        std::cin >> userInput;
        if (userInput == indexCorrectAnswer) {
            std::cout << "Correct Answer!" << "\n\n";
        } else {
            std::cout << "Wrong!\nCorrect Answer: " << indexCorrectAnswer << ". " << correctAnswer << "\n\n";
        }
    }
    std::cout << "\n\n----QUIZ END----\n\n";
}

json loadJsonFromFile(std::string path) { return json::parse(std::ifstream(path)); }

void UseTestQuizzes() {
    std::string exampleQuizPath  = "./examplequizzes";
    json exampleQuiz1 = loadJsonFromFile(exampleQuizPath + "/quiz1.json");
    json exampleQuiz2 = loadJsonFromFile(exampleQuizPath + "/quiz2.json");
    std::cout << "RUNNING exampleQuiz1:\n\n";
    RunQuiz(exampleQuiz1);
    std::cout << "RUNNING exampleQuiz2:\n\n";
    RunQuiz(exampleQuiz2);
}

const int ARGC_WHEN_NO_ARGUMENTS = 1;

int main(int argc, char **argv) {
    // if (argv[1] == "-h"){
    //     // TODO: Make a better help page
    //     std::cout << "Usage: ./quizzies [<path>]\n\nPlay a Quiz with the json ";
    // } else if (argc > ARGC_WHEN_NO_ARGUMENTS) {
    //     UseTestQuizzes();
    // } else {
    //     RunQuiz(loadJsonFromFile(argv[1]));
    // }
    getQuestionTypeFromJson(loadJsonFromFile(""));
    return 0;
}

