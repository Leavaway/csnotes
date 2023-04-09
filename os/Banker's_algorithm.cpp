#include <iostream>
#include <vector>

int rows = 5;
int cols = 3;
std::vector<std::vector<int>> max_matrix(rows, std::vector<int>(cols, 0));
std::vector<std::vector<int>> allo_matrix(rows, std::vector<int>(cols, 0));
std::vector<std::vector<int>> need_matrix(rows, std::vector<int>(cols, 0));
std::vector<int> Available {3,3,2};


bool banker(std::vector<int>& request){
    for (size_t i = 0; i < cols; i++)
    {
      if(request.at(i+1)>need_matrix[request.at(0)][i]){
        return false;
      }
      if(request.at(i+1)>Available.at(i)){
        //block progress here.
        return false;
      }
    }
    for (size_t i = 0; i < cols; i++)
    {
      Available[i] = Available[i] - request[i+1];
      allo_matrix[request.at(0)][i] = allo_matrix[request.at(0)][i] + request[i+1];
      need_matrix[request.at(0)][i] = need_matrix[request.at(0)][i] - request[i+1];
    }
    
    //conduct safe check
    bool safe = false;
    for (size_t i = 0; i < rows; i++)
    {
      bool safe2 = true;
      for (size_t j = 0; j < cols; j++)
      {
        if(Available[j]<need_matrix[i][j]){
          safe2 = false;
        }
      }
      if(safe2){
        safe = true;
      }
      
    }   

    //if unsafe, then restore.
    if(!safe){
      for (size_t i = 0; i < cols; i++) {
        Available[i] += request[i + 1];
        allo_matrix[request.at(0)][i] -= request[i + 1];
        need_matrix[request.at(0)][i] += request[i + 1];
      }
    }
    return safe;
}



int main() {
    max_matrix[0] = std::vector<int>{7, 5, 3};
    max_matrix[1] = std::vector<int>{3, 2, 2};
    max_matrix[2] = std::vector<int>{9, 0, 2};
    max_matrix[3] = std::vector<int>{2, 2, 2};
    max_matrix[4] = std::vector<int>{4, 3, 3};

    allo_matrix[0] = std::vector<int>{0, 1, 0};
    allo_matrix[1] = std::vector<int>{2, 0, 0};
    allo_matrix[2] = std::vector<int>{3, 0, 2};
    allo_matrix[3] = std::vector<int>{2, 1, 1};
    allo_matrix[4] = std::vector<int>{0, 0, 2};

    for (size_t i = 0; i < rows; i++)
    {
      for (size_t j = 0; j < cols; j++)
      {
        need_matrix[i][j] = max_matrix[i][j] - allo_matrix[i][j];
      }
    }



    std::vector<int> Request {0,2,1,1};
    
    std::cout<<"The result of banker's algorithm is: " << banker(Request) << '\n';

    return 0;
}

