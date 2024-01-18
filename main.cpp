#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include <filesystem>
#include <string>
#include <random>
#include <vector>

#include "include/json.hpp"


constexpr int ARGC_WHEN_NO_ARGUMENTS = 1;


std::vector<std::string> mixItUp(std::vector<std::string> vec) {
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(vec), std::end(vec), rng);
    return vec;
}

bool OSIsWindows(){
#ifdef _WIN32 // _WIN64 isn't checked because if _WIN64 is defined then _WIN32 is defined too
    return true;
#elif __CYGWIN__ 
    return true;
#else
    return false;
#endif
}

enum QuestionType {
    MultipleChoice,  // TODO: Make Example Questions of this type
    TrueOrFalse,
    Estimation  // TODO: Make Example Questions of this type
};

// Could also be a struct
class Question {
private:
    QuestionType _questionType;
    std::vector<std::string> _wrongAnswers;
    std::string _rightAnswer;
public:
    std::vector<std::string> AllAnswers;
    std::string QuestionSentence;
    Question(QuestionType questiontype, std::string question,
            std::vector<std::string> wronganswers, std::string rightanswer) {
        _questionType = questiontype;
        _wrongAnswers = wronganswers;
        _rightAnswer = rightanswer;
        QuestionSentence = question;
        AllAnswers = std::vector(_wrongAnswers);
        AllAnswers.push_back(_rightAnswer);
        AllAnswers = mixItUp(AllAnswers);
    }

    int GetIndexOfRightAnswer() {
         return std::find(AllAnswers.begin(), AllAnswers.end(), _rightAnswer) - AllAnswers.begin();
    }
};

class Quiz {
public: 
    std::vector<Question> Questions;
    Quiz(std::vector<Question> questions){
        Questions = questions;
    }
};

using json = nlohmann::json;

// Can't name the parameter "json" because json is already defined as a type above
// The Json needs to be a valid quiz
bool JsonIsValidQuiz(json jsonObject) {
    // TODO
    return false;
}

void UseTestQuizzes() {
    // TODO
    std::string exampleQuizPath  = "./examplequizzes";
    json exampleQuiz1 = json::parse(std::ifstream(exampleQuizPath + "/quiz1.json"));
    json exampleQuiz2 = json::parse(std::ifstream(exampleQuizPath + "/quiz2.json"));
    
    for(auto Question : exampleQuiz1) {
        for(auto Answer : Question){
            // TODO: Find out, how to display the Keys
            std::cout << Answer << "\n";
        }
        std::cout << "\n";
    }
}



void CheckArgv(int argc, char **argv) {
    if (argv[1] == "-h"){
        // TODO: Make a better help page
        std::cout << "Usage: ./quizzies [<path>]\n\nPlay a Quiz with the json ";
    }
}


int main(int argc, char **argv) {
    if (argc > ARGC_WHEN_NO_ARGUMENTS) {
        CheckArgv(argc, argv);
    } else {
        UseTestQuizzes();
    }

    return 0;
}

