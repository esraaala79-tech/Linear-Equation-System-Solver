#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
using namespace std;

float a[100][100] = {0};
float b[100] = {0};
int n;
int vars = 0;

/* ================= Determinant ================= */

float determinant(float mat[100][100], int size)
{
    if (size == 1)
        return mat[0][0];

    float det = 0;
    float sub[100][100];

    for (int x = 0; x < size; x++)
    {
        int subi = 0;
        for (int i = 1; i < size; i++)
        {
            int subj = 0;
            for (int j = 0; j < size; j++)
            {
                if (j == x)
                    continue;
                sub[subi][subj] = mat[i][j];
                subj++;
            }
            subi++;
        }

        if (x % 2 == 0)
            det += mat[0][x] * determinant(sub, size - 1);
        else
            det -= mat[0][x] * determinant(sub, size - 1);
    }

    return det;
}

/* ================= Print Equation Proper Form ================= */

void printEquation(float row[], float rhs)
{
    bool first = true;

    for (int j = 0; j < vars; j++)
    {
        if (row[j] != 0)
        {
            if (!first)
            {
                if (row[j] > 0) cout << "+";
            }

            if (row[j] == 1)
                cout << "x" << j + 1;
            else if (row[j] == -1)
                cout << "-x" << j + 1;
            else
                cout << row[j] << "x" << j + 1;

            first = false;
        }
    }

    cout << "=" << rhs << endl;
}

/* ================= Substitute ================= */

void substituteVar(int varIndex, int eq1, int eq2)
{
    float coeff = a[eq1][varIndex];

    if (coeff == 0)
    {
        printEquation(a[eq1], b[eq1]);
        return;
    }

    float pivot = a[eq2][varIndex];

    for (int j = 0; j < vars; j++)
    {
        if (j != varIndex)
            a[eq1][j] -= coeff * (a[eq2][j] / pivot);
    }

    b[eq1] -= coeff * (b[eq2] / pivot);
    a[eq1][varIndex] = 0;

    printEquation(a[eq1], b[eq1]);
}

/* ================= Main ================= */

int main()
{
    cin >> n;
    cin.ignore();

    string line;

    /* ====== Read Equations ====== */

    for (int i = 0; i < n; i++)
    {
        getline(cin, line);

        int sign = 1;
        string temp = "";
        bool rightSide = false;

        for (int j = 0; j < line.length(); j++)
        {
            if (line[j] == '+')
                sign = 1;

            else if (line[j] == '-')
                sign = -1;

            else if (line[j] == '=')
            {
                rightSide = true;
                sign = 1;
                temp = "";
            }

            else if (line[j] == 'x')
            {
                j++;
                int index = line[j] - '1';
                if (index + 1 > vars)
                    vars = index + 1;

                float num;
                if (temp == "")
                    num = 1;
                else
                    num = atof(temp.c_str());

                a[i][index] += sign * num;
                temp = "";
            }

            else if (isdigit(line[j]) || line[j] == '.')
                temp += line[j];
        }

        if (temp != "")
            b[i] = atof(temp.c_str());
    }

    /* ====== Commands ====== */

    string command;

    while (cin >> command)
    {
        if (command == "quit")
            break;

        /* Level 1 */

        if (command == "num_vars")
        {
            cout << vars << endl;
        }

        else if (command == "equation")
        {
            int idx;
            cin >> idx;
            printEquation(a[idx - 1], b[idx - 1]);
        }

        else if (command == "column")
        {
            string var;
            cin >> var;
            int col = var[1] - '1';

            for (int i = 0; i < n; i++)
                cout << a[i][col] << endl;
        }

        /* Level 2 */

        else if (command == "add")
        {
            int e1, e2;
            cin >> e1 >> e2;

            float result[100] = {0};

            for (int j = 0; j < vars; j++)
                result[j] = a[e1 - 1][j] + a[e2 - 1][j];

            printEquation(result, b[e1 - 1] + b[e2 - 1]);
        }

        else if (command == "subtract")
        {
            int e1, e2;
            cin >> e1 >> e2;

            float result[100] = {0};

            for (int j = 0; j < vars; j++)
                result[j] = a[e1 - 1][j] - a[e2 - 1][j];

            printEquation(result, b[e1 - 1] - b[e2 - 1]);
        }

        else if (command == "substitute")
        {
            string var;
            int e1, e2;
            cin >> var >> e1 >> e2;

            int varIndex = var[1] - '1';
            substituteVar(varIndex, e1 - 1, e2 - 1);
        }

        /* Level 3 */

        else if (command == "D")
        {
            string var;
            if (cin.peek() == '\n')
            {
                for (int i = 0; i < vars; i++)
                {
                    for (int j = 0; j < vars; j++)
                        cout << a[i][j] << " ";
                    cout << endl;
                }
            }
            else
            {
                cin >> var;
                int col = var[1] - '1';

                float temp[100][100];

                for (int i = 0; i < vars; i++)
                    for (int j = 0; j < vars; j++)
                        temp[i][j] = a[i][j];

                for (int i = 0; i < vars; i++)
                    temp[i][col] = b[i];

                for (int i = 0; i < vars; i++)
                {
                    for (int j = 0; j < vars; j++)
                        cout << temp[i][j] << " ";
                    cout << endl;
                }
            }
        }

        else if (command == "D_value")
        {
            float mat[100][100];

            for (int i = 0; i < vars; i++)
                for (int j = 0; j < vars; j++)
                    mat[i][j] = a[i][j];

            cout << determinant(mat, vars) << endl;
        }

        else if (command == "solve")
        {
            float mat[100][100];

            for (int i = 0; i < vars; i++)
                for (int j = 0; j < vars; j++)
                    mat[i][j] = a[i][j];

            float D = determinant(mat, vars);

            if (D == 0)
            {
                cout << "No Solution" << endl;
                continue;
            }

            for (int v = 0; v < vars; v++)
            {
                float temp[100][100];

                for (int i = 0; i < vars; i++)
                    for (int j = 0; j < vars; j++)
                        temp[i][j] = a[i][j];

                for (int i = 0; i < vars; i++)
                    temp[i][v] = b[i];

                float Dx = determinant(temp, vars);

                cout << "x" << v + 1 << "=" << Dx / D << endl;
            }
        }
    }

    return 0;
}