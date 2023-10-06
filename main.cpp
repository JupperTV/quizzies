#include <iostream>
#include <string>
#include <random>
#include <vector>

std::vector<std::string> mixItUp(std::vector<std::string> vec){
    std::vector<std::string> retVec { };
    std::random_device seedgenerator;
    std::mt19937 numbergenerator(seedgenerator());
    std::uniform_int_distribution<> distributor(0, vec.size());
    for (std::size_t i = 0; i < vec.size(); ++i){
        retVec.push_back(vec[distributor(numbergenerator)]);
    }
    return retVec;
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
    int indexOfRightAnswer = -1;
    Question(QuestionType questiontype, std::vector<std::string> wronganswers, std::string rightanswer) {
        _questionType = questiontype;
        _wrongAnswers = wronganswers;
        _rightAnswer = rightanswer;
    }

    std::vector<std::string> MixUpAnswers() {
        std::vector<std::string> copy = _wrongAnswers;
        copy.push_back(_rightAnswer);
        return mixItUp(copy);
    }
};

class Quiz {
public:
    Quiz(std::vector<Question> questions);
};

int main() {
    std::vector<std::string> vec{"abc", "fdf", "dfs", "vcx", "löd", "yxb"};
    std::vector<std::string> vec2 = mixItUp(vec);
    for (std::string s : vec){
        std::cout << s << '\n';
    }
    std::cout << "\n\n";
    for (std::string s : vec2){
        std::cout << s << '\n';
    }
    return 0;
}
