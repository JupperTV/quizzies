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


/*
 * The classes Quiz, Question, and the enum QuestionType exists for the creation of quizzes
*/

using json = nlohmann::json;

// Can't name the parameter "json" because json is already defined as a type above
// The Json needs to be a valid quiz
bool JsonIsValidQuiz(json jsonObject) {
    // TODO
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

json loadJsonFromFile(std::string path) {
    return json::parse(std::ifstream(path));
}

void UseTestQuizzes() {
    std::string exampleQuizPath  = "./examplequizzes";
    json exampleQuiz1 = loadJsonFromFile(exampleQuizPath + "/quiz1.json");
    json exampleQuiz2 = loadJsonFromFile(exampleQuizPath + "/quiz2.json");
    std::cout << "RUNNING exampleQuiz1:\n\n";
    RunQuiz(exampleQuiz1);
    std::cout << "RUNNING exampleQuiz2:\n\n";
    RunQuiz(exampleQuiz2);
}

constexpr int ARGC_WHEN_NO_ARGUMENTS = 1;

int main(int argc, char **argv) {
    if (argv[1] == "-h"){
        // TODO: Make a better help page
        std::cout << "Usage: ./quizzies [<path>]\n\nPlay a Quiz with the json ";
    } else if (argc > ARGC_WHEN_NO_ARGUMENTS) {
        UseTestQuizzes();
    } else {
        RunQuiz(loadJsonFromFile(argv[1]));
    }

    return 0;
}

