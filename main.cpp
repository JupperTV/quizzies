#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
// #include <nlohmann/json.hpp>
#include "include/json.hpp"
#include <string>
#include <random>
#include <vector>

std::vector<std::string> mixItUp(std::vector<std::string> vec) {
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(vec), std::end(vec), rng);
    return vec;
}

enum QuestionType {
    MultipleChoice,
    TrueOrFalse,
    Estimation
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

void DoTestWithTestQuizzes() {
    
}

void ExampleQuizzes(){
    Question q1 = Question(MultipleChoice, "What is the shape of the earth?",
            std::vector<std::string> {"Flat", "Odd", "Triangular"}, "Round");
    Question q2 = Question(MultipleChoice, "What is the shape of the sun?",
            std::vector<std::string> {"Odd", "Triangular", "Flat"}, "Round");
    std::vector<Question> questions = {q1, q2};
    Quiz qz = Quiz(questions);
    for (Question question : qz.Questions) {
        std::cout << question.QuestionSentence << "\n";
        for (std::string answer : question.AllAnswers) {
            std::cout << "\t" << answer << "\n";
        }
        std::cout << '(' << question.GetIndexOfRightAnswer() << ")\n";
    }
    // TODO: Use stuff from ./examplequizzes as tests
}


using json = nlohmann::json;
json LoadJson(const char filename[]){
    return json::parse(std::ifstream(filename));
}

int main(int argc, char **argv) {
    json quiz = LoadJson("layoutForQuestions.json");

    return 0;
}
