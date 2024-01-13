#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include <filesystem>
#include <string>
#include <random>
#include <vector>

#include "include/json.hpp"

std::vector<std::string> mixItUp(std::vector<std::string> vec) {
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(vec), std::end(vec), rng);
    return vec;
}

// TODO
bool OSIsWindows(){
    #ifdef _WIN32 || _WIN64 || __CYGWIN__
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

void UseTestQuizzes() {

}

int main(int argc, char **argv) {
    json quiz = json::parse(std::ifstream("layoutForQuestions.json"));
    // std::filesystem::
    return 0;
}
