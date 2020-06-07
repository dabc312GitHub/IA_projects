// Viajerominimizar.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <time.h>
#include <map>
#include <math.h>

using namespace std;

#define npoblacion 100
#define numeroviajeros 10
#define niteraciones 1000
#define tamano 100

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


string letras[] = { "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","0","1","2","3","4","5","6","7","8","9" };

void bubbleSort(vector<string>& p, vector<float>& arr)
{
    int i, j;
    for (i = 0; i < arr.size() - 1; i++)
        for (j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float tem = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tem;
                string tem1 = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tem1;

            }
        }
}


double func(string a, map<string, pair<int, int>> coords) {
    double res = 0;
    for (int i = 0; i < a.length() - 1; ++i) {
        string xd = "";
        xd = xd + a[i];
        string xd1 = "";
        xd1 = xd1 + a[i + 1];
        double temp = 0.0;
        temp = pow(coords[xd].first - coords[xd1].first, 2.0)+ pow(coords[xd].second - coords[xd1].second, 2.0);
        temp = sqrt(temp);
        res += temp;
    }
    string xd = "";
    xd = xd + a[0];
    string xd1 = "";
    xd1 = xd1 + a[a.length()-1];
    double temp = 0.0;
//    cout <<" "<< xd << " " << xd1 << endl;
    temp = pow(coords[xd].first - coords[xd1].first, 2.0) + pow(coords[xd].second - coords[xd1].second, 2.0);
    temp = sqrt(temp);
    res += temp;
    return res;
}

void mezclar(string& a, string& b) {
    string auxa = "";
    string auxb = "";
    auxa.insert(0, "-----------------------------------------------------------", numeroviajeros);
    auxb.insert(0, "-----------------------------------------------------------", numeroviajeros);
    string mascara = "1000010";
    for (int i = 0; i < a.length(); ++i) {
        int xd = rand() % mascara.length();
        if (mascara[xd] == '1') {
            auxa[i] = b[i];
            auxb[i] = a[i];
        }
    }
//    cout << a << " " << b << endl;
  //  cout << auxa << " " << auxb << endl;
    int posa = 0;
    int cont = 0;
    while (posa < a.length() && cont < a.length()) {
        if (string::npos == auxa.find(a[cont])) {//no lo encuentro
            if (auxa[posa] == '-') {
                auxa[posa] = a[cont];
            }
            else {
                posa++;
            }
        }
        else {
            cont++;
        }
    }
    posa = 0;
    cont = 0;
    while (posa < b.length() && cont < b.length()) {
        if (string::npos == auxb.find(b[cont])) {//no lo encuentro
            if (auxb[posa] == '-') {
                auxb[posa] = b[cont];
            }
            else {
                posa++;
            }
        }
        else {
            cont++;
        }
    }
    //cout << a << " " << b << endl;
    //cout << auxa << " " << auxb << endl;
    a = auxa;
    b = auxb;
}

vector<string> cruzamiento(vector<string>& padres) {
    int cont = 0;
    int pos = 0;
    vector<string> nuevapoblacion;
    for (int i = 0; i < npoblacion / 2; ++i) {
        int r1 = rand() % padres.size();
        int r2 = rand() % padres.size();
        string a, b;
        a = padres[r1];
        b = padres[r2];
        mezclar(a, b);
        nuevapoblacion.push_back(a);
        nuevapoblacion.push_back(b);
    }
    return nuevapoblacion;
}
void seleccion(vector<string>& p, vector<float>& a, float media) {
    int cont = 0;
    vector<string> padres;
    int pos = 0;
    while (cont < npoblacion && pos != npoblacion) {

        const double repetir = static_cast<int>(a[pos] / media * 1.0 + 0.5) / 1.0;
        if (repetir != 1.0)cout << 123 << endl;
        for (int i = 0; i < npoblacion / 8; ++i) {
            padres.push_back(p[pos]);
        }
//        cout << p[pos] <<" "<< a[pos] / media << " " <<repetir<< endl;
//        cont += repetir;
        cont += npoblacion / 8;
        pos++;
    }
  //  cout << endl;
    vector<string> nuevos = cruzamiento(padres);
    p = nuevos;
  /*  for (int i = 0; i < padres.size(); ++i) {
        cout << padres[i] << endl;
    }*/
}



int algoritmo(float cxy[30],unsigned int ind[30]) {
    vector<string> poblacion;
    map<string, pair<int, int>> coords;
    for (int j = 0; j < npoblacion; ++j) {
        string prueba = "a";
        for (int i = 1; i < numeroviajeros; ++i) {
            int pos = rand() % (1 + prueba.length());
            prueba.insert(pos, letras[i]);
        }
        poblacion.push_back(prueba);
    }
    for (int i = 0; i < numeroviajeros; ++i) {
        coords[letras[i]] = (pair<int, int>(rand() % tamano, rand() % tamano));
    }
    for (int i = 0; i < numeroviajeros; ++i) {
        cout << letras[i] << " -> " << coords[letras[i]].first << " " << coords[letras[i]].second << endl;
        cxy[i * 3] = (coords[letras[i]].first / 50.0) - 1.0;
        cxy[(i * 3) + 1] = (coords[letras[i]].second / 50.0) - 1.0;
        cxy[(i * 3) + 2] = 0.0;
    }

    /*
    //vector<float> aptitud2; 
    //for (int i = 0; i < npoblacion; ++i) {
    //    float temp = func(poblacion[i], coords);
    //    aptitud2.push_back(temp);
    //}
    //bubbleSort(poblacion, aptitud2);
    // cout << poblacion[0] << endl;
    //cout << func(poblacion[0], coords) << " " << endl;
    //cout << func(poblacion[npoblacion-1], coords) << " " << endl;
    //iteraciones
    */
    
    for (int xdd = 0; xdd < niteraciones; ++xdd) {
        float media = 0.0;
        vector<float> aptitud;
        for (int i = 0; i < npoblacion; ++i) {
            float temp = func(poblacion[i], coords);
            aptitud.push_back(temp);
            media += temp;
        }
        media /= npoblacion;
        bubbleSort(poblacion, aptitud);
        //cout << "Media = " << media << endl;
        
        
        seleccion(poblacion, aptitud, media);
        /*
        for (int i = 0; i < npoblacion; ++i) {
            cout << poblacion[i] << " " << aptitud[i] << " " << endl;
            //        cout << func(poblacion[i], coords) << endl;
        }
        //*/
    }
    cout << func(poblacion[0], coords)<<endl;
    cout << poblacion[0] << endl;

    string alf = "abcdefghijklmnopqrstuvwxyz";
    
    poblacion[0] += poblacion[0][0];
    for (int i = 0; i < 10; ++i) {
        ind[(i * 3) + 0] = alf.find(poblacion[0][i]);
        ind[(i * 3) + 1] = (alf.find(poblacion[0][i+1])) % 10;
        ind[(i * 3) + 2] = alf.find(poblacion[0][i]);
    }
    return 1;
}

int main()
{
    float a[30];
    unsigned int ind[30];
    srand(time(NULL));
    algoritmo(a, ind);
    /*for (int i = 0; i < 10; ++i) {
        cout << a[i * 3] << " " << a[(i * 3) + 1] << " " << a[(i * 3) + 2] << endl;
    }*/

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int indices[30];
    for (int i = 0; i < 9; ++i) {
        indices[(i * 3) + 0] = i;
        indices[(i * 3) + 1] = i + 1;
        indices[(i * 3) + 2] = i;
    }
    indices[(27) + 0] = 0;
    indices[(27) + 1] = 9;
    indices[(27) + 2] = 0;
 /*   for (int i = 0; i < 10; ++i) {
        cout << indices[(i * 3) + 0] << " ";
        cout << indices[(i * 3) + 1] << " ";
        cout << indices[(i * 3) + 2] << endl;
    }
    cout << endl;
   /// for (int i = 0; i < 10; ++i) {
        cout << ind[(i * 3) + 0] << " ";
        cout << ind[(i * 3) + 1] << " ";
        cout << ind[(i * 3) + 2] << endl;
    }*/
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(a), a, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); 
        glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;

}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}