#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <shader_s.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/vec3.hpp> //pra usar vectores 3D
#include <glm/glm.hpp>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <ctime>
#include <sys\timeb.h> 

#include <chrono>
#include <thread>
/*const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";*/
const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.8f, 1.0f);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void rectangulo(float ladoA, float ladoB, float c1,float c2,float c3);
void circulo(float x, int y,float c1,float c2,float c3); //recibe radio y numero de puntos

std::vector<glm::vec3> vertices0;//se usa en funcion circulo
std::vector<glm::vec3> vertices1;//se usa en funcion rectangulo
std::vector<glm::vec3> vertices2;//auxiliar para meter valores al VAO
std::vector<glm::vec3> vertices3;//se usa en funcion circulo

int main()
{
    using namespace std::this_thread;
    using namespace std::chrono_literals;
    using std::chrono::system_clock;
    //lo aonterior para delay
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(800, 900, "Texturas OpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }

    // build and compile our shader program
    //glEnable(GL_DEPTH_TEST);
    Shader ourShader("5.1.transform.vs", "5.1.transform.fs");
    //glEnable(GL_DEPTH_TEST);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.4f, 0.0f,  // 4.0f, 4.0f, // top right
         0.5f, -0.4f, 0.0f,   //4.0f, 0.0f, // bottom right
        -0.5f, -0.4f, 0.0f,   //0.0f, 0.0f, // bottom left
        -0.5f,  0.4f, 0.0f   //0.0f, 4.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramOrange = glCreateProgram();
    glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShaderOrange);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);

    unsigned int VBO[15], VAO[15], EBO[5];
    glGenVertexArrays(15, VAO);
    glGenBuffers(15, VBO);
    glGenBuffers(5, EBO);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    

    
    rectangulo(0.6,1.2,1.0f,0.2f,0.0f); //altura ancho, rojo
    vertices2 = vertices1;
    vertices1.clear();//muy importamte limpiar para que use de nuevo en la funcion rectangulo
    
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    rectangulo(0.04, 0.6, 1.0f, 1.0f, 0.8f);//Rectanulos pequenos izq
    vertices2 = vertices1;
    vertices1.clear();//muy importamte limpiar para que use de nuevo en la funcion rectangulo

    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    rectangulo(0.04, 0.35, 1.0f, 1.0f, 0.8f);//Rectanulos pequenos der
    vertices2 = vertices1;
    vertices1.clear();//muy importamte limpiar para que use de nuevo en la funcion rectangulo

    glBindVertexArray(VAO[6]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    rectangulo(0.99, 0.04, 1.0f, 1.0f, 0.8f);//Rectanulos pequenos horizontal
    vertices2 = vertices1;
    vertices1.clear();//muy importamte limpiar para que use de nuevo en la funcion rectangulo

    glBindVertexArray(VAO[7]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[7]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    rectangulo(0.35, 0.04, 1.0f, 1.0f, 0.8f);//Rectangulos horizontal blanco arriba
    vertices2 = vertices1;
    vertices1.clear();//muy importamte limpiar para que use de nuevo en la funcion rectangulo

    glBindVertexArray(VAO[8]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[8]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    rectangulo(0.35, 0.04, 0.0f, 0.0f, 0.0f);//Rectangulos horizontal negro arriba
    vertices2 = vertices1;
    vertices1.clear();//muy importamte limpiar para que use de nuevo en la funcion rectangulo

    glBindVertexArray(VAO[9]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[9]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    rectangulo(1.1, 0.01, 0.0f, 0.0f, 0.0f);//linea negra (palo)
    vertices2 = vertices1;
    vertices1.clear();//

    glBindVertexArray(VAO[10]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[10]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    rectangulo(2.8, 0.01, 0.0f, 0.0f, 0.0f);//linea negra para final
    vertices2 = vertices1;
    vertices1.clear();//

    glBindVertexArray(VAO[11]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[11]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    rectangulo(2.8, 0.01, 1.0f, 1.0f, 0.8f);//linea blanca para final
    vertices2 = vertices1;
    vertices1.clear();//

    glBindVertexArray(VAO[12]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[12]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    rectangulo(0.95, 1.0, 1.0f, 1.0f, 0.8f); //ancho altura, rectangulo blanco grande
    vertices2 = vertices1;
    vertices1.clear();//muy importamte limpiar para que use de nuevo en la funcion rectangulo

    glBindVertexArray(VAO[5]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //
    // circulo
    circulo(0.25, 50,0.2f,0.2f,0.2f);
    vertices3 = vertices0;
    vertices0.clear();
    /*for (int i = 0; i < 144; i++) {
        vertices3[i][0] = vertices3[i][0] -0.4f;
        vertices3[i][1] = vertices3[i][1] + 0.15f;

    }*/
    glBindVertexArray(VAO[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices3.size(), &vertices3[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //
    float verticesA[] = {
        // positions          // colors           // texture coords
         0.4f,  0.4f, 0.0f,   1.0f, 0.0f, 0.0f,  // 1.0f, 1.0f, // top right
         0.4f, -0.4f, 0.0f,   1.0f, 0.0f, 0.0f,   //1.0f, 0.0f, // bottom right
        -0.4f, -0.4f, 0.0f,   1.0f, 0.0f, 0.0f,   //0.0f, 0.0f, // bottom left
        -0.4f,  0.4f, 0.0f,   1.0f, 0.0f, 0.0f   //0.0f, 1.0f  // top left 
    };
    unsigned int indicesA[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    float verticesB[] = {
        // positions         // colors
         0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.0f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // top 

         0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom left
         0.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f   // top 
    };
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB), verticesB, GL_STATIC_DRAW);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesA), indicesA, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    float radius = 0.4f;//entre mas grande el radio la corcunferencia sobre la cual rota la camara es mas grande
        //y ves los objetos mas lejos
    float camX = 360;
    float camY = 360;
    float x, y;
    float a = -0.8;
    ourShader.use();
    //ourShader.setInt("texture", 0);
    struct timeb start, end;
    unsigned short elapse = 0, t1, t2;
    float inc = 0;// 3.14;
    float inc2 = 0;
    float der = -1.3f;
    float der2 = -1.3f;
    float der3 = -1.6f;
    float abajo = 1.8f;
    float diagA = -1.18f;
    float diagB = -0.17f;
    float aux = 1.0f;
    float aux2 = 1.6f;
    float aux3 = 1.6f;
    float aux4 = 1.6f;
    float aux5 = 1.6f;
    float tiempo = 0.01f; //variable para manjear tiempo de escenas
    bool flag = true;
    bool flag1 = true;
    bool flag3 = true;
    //para personaje
    float per1 = -1.4f;
    float per2 = 0.0f;
    float pal1 = -1.4f;
    //para parte donde cae personaje
    float abajoP;
    float abajoP2;
    float caer1 = 0.6;
    float caer2=0.28;
    float caer3=0.2;
    float caer4=0.28;
    float caer5;
    ftime(&start);
    t1 = start.millitm;
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // keyboard input
        processInput(window);
        
        ftime(&end);
        t2 = end.millitm;
        elapse = t2-t1;//loque metardo en construir un marco en milisegundos
        //si no ha paso el valor no entro (repito marco anterior), si entro mucho cambio

        if (elapse > 20) {//esto es lo que cambias, asi entro o no entro al elapse, si entro cambio marco sino entro se queda marco,
            //entre mas pqueno el numero 
            tiempo += 0.003f;
            t1 = t2;
            // render
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            //
           /* glUseProgram(shaderProgramOrange);

            glBindVertexArray(VAO[0]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/


            //  glBindVertexArray(VAO[4]);
              //glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
              // bind Texture
             // glActiveTexture(GL_TEXTURE0);
             // glBindTexture(GL_TEXTURE_2D, texture);
            x = cos(glfwGetTime()) * radius;
            y = sin(glfwGetTime()) * radius;
            // create transformations
            //inc es e; angulo aumnetarlo es girar contra reloj, decremnto es sentido horario
            //inc = inc + 0.007;//entre mas grande mas saltado se va a ver, menos smooth pues los saltos del angulo son muy grandes
            inc2 = inc2 - 0.01;
            if (aux > -1.0f && flag) {
                aux = aux - 0.01;
            }
            else {
                aux = aux + 0.01;
                flag = false;
                if (aux == 1.0f)
                    flag = true;
            }
            //abajo -= 0.01;

            glm::mat4 abajo1 = glm::mat4(1.0f);
            glm::mat4 abajo2 = glm::mat4(1.0f);

            glm::mat4 transform = glm::mat4(1.0f);
            glm::mat4 transform0 = glm::mat4(1.0f); // Para 
            glm::mat4 transform1 = glm::mat4(1.0f);
            glm::mat4 transform2 = glm::mat4(1.0f);
            glm::mat4 transform3 = glm::mat4(1.0f);
            glm::mat4 transform4 = glm::mat4(1.0f);
            glm::mat4 transform5 = glm::mat4(1.0f);
            glm::mat4 transform6 = glm::mat4(1.0f);
            glm::mat4 transform7 = glm::mat4(1.0f);
            glm::mat4 transform8 = glm::mat4(1.0f);
            glm::mat4 transform9 = glm::mat4(1.0f);
            glm::mat4 caer = glm::mat4(1.0f);
            glm::mat4 caerA = glm::mat4(1.0f);
            glm::mat4 caerB = glm::mat4(1.0f);
            glm::mat4 caerC = glm::mat4(1.0f);
            glm::mat4 caerD = glm::mat4(1.0f);

            glm::mat4 personaje = glm::mat4(1.0f);
            glm::mat4 palo = glm::mat4(1.0f);
            glm::mat4 palo1 = glm::mat4(1.0f);
            glm::mat4 palo2 = glm::mat4(1.0f);

            glm::mat4 igual = glm::mat4(1.0f);
            glm::mat4 igual2 = glm::mat4(1.0f);
            glm::mat4 igual3 = glm::mat4(1.0f);
            glm::mat4 igual4 = glm::mat4(1.0f);
            glm::mat4 igual5 = glm::mat4(1.0f);
            glm::mat4 igual6 = glm::mat4(1.0f);

            igual = glm::translate(igual, glm::vec3(-0.1f, -0.08f, 0.0f));

            igual2 = glm::scale(igual2, glm::vec3(0.85f));
            igual2 = glm::translate(igual2, glm::vec3(0.8f, 0.6f, 0.0f));

            igual3 = glm::translate(igual3, glm::vec3(0.8f, 0.28f, 0.0f));
            igual4 = glm::translate(igual4, glm::vec3(0.5f, 0.28f, 0.0f));

            igual5 = glm::translate(igual3, glm::vec3(0.0f, -0.07f, 0.0f));
            igual6 = glm::translate(igual4, glm::vec3(0.0f, -0.07f, 0.0f));

            //inc va cambiando el angulo de rotacion
            //rotacion, angulo en radiana y eje de rotacion
            transform0 = glm::rotate(transform0, -0.6f, glm::vec3(0.0f, 0.0f, 1.0f));//para VAO[5] rectangulo blkanco de atras
            transform0 = glm::translate(transform0, glm::vec3(-0.2f, 0.08f, 0.0f));
            transform0 = glm::scale(transform0, glm::vec3(1.2f));

            //transform = glm::rotate(transform, (float)inc, glm::vec3(0.0f, 0.0f, 1.0f));
            transform = glm::rotate(transform, 1.57f, glm::vec3(0.0f, 0.0f, 1.0f));
            transform = glm::translate(transform, glm::vec3(-0.17f, 0.11f, 0.0f));//0.11 (arriba/abajo,der/izq,_) para bajar resto para mover a izq sumo
            // transform1 = glm::rotate(transform1, (float)inc2, glm::vec3(0.0f, 0.0f, 1.0f));
            //transform1 = glm::translate(transform1, glm::vec3(aux, 0.0f, 1.0f));//movimiento izq-der o der-izq
            transform1 = glm::translate(transform1, glm::vec3(der, -0.08f, 1.0f));
            //transform2 = glm::translate(transform2, glm::vec3(0.0f, aux, 1.0f));//mov arriba abajo 0 abajo arriba
            transform2 = glm::scale(transform2, glm::vec3(0.85f));
            transform2 = glm::translate(transform2, glm::vec3(0.8f, abajo, 0.0f));

            transform3 = glm::translate(transform3, glm::vec3(x, y, 0.0f)); //circunerencia

            transform4 = glm::translate(transform4, glm::vec3(-aux, aux / 0.4, 0.0f)); //diagonal, dividiendo ajustas pendiente

            transform8 = glm::translate(transform8, glm::vec3(der2, 0.28, 0.0f));

            transform9 = glm::translate(transform9, glm::vec3(der3, 0.28, 0.0f));

            abajo1 = glm::translate(transform8, glm::vec3(0.0f, -0.07f, 0.0f));

            abajo2 = glm::translate(transform9, glm::vec3(0.0f, -0.07f, 0.0f));

            personaje = glm::scale(personaje, glm::vec3(0.7f));

            //palo = glm::translate(palo, glm::vec3(-0.45f, 0.1f, 0.0f));
           // palo = glm::rotate(palo, 0.78f, glm::vec3(pal1, 0.0f, 1.0f));
            //por la rotacion cuidado con los vambios en x y y
            // render container
            ourShader.use();
            unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");



            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform0));

            glBindVertexArray(VAO[5]);//cuadro blancoa atras
            glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

            //  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform3));//vao4 es circulo
              //glBindVertexArray(VAO[4]);
              //glDrawArrays(GL_TRIANGLES, 0, vertices3.size());


                  //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform1));


          //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform5));
            transform5 = glm::translate(transform5, glm::vec3(-0.8, -0.6f, 1.0f));
            if (tiempo > 0.15) {
                der += 0.01;
                if (aux2 > (0.1)) {
                    aux2 -= 0.01;
                }
                //for (int i = 0; i < 7; i++) {

                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform5));
                transform5 = glm::translate(transform5, glm::vec3(0.06, 0.0f, 0.0f));
                glBindVertexArray(VAO[3]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                transform6 = glm::translate(transform6, glm::vec3(0.6, -0.5f, 1.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform6));
                glBindVertexArray(VAO[6]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());



                transform7 = glm::translate(transform7, glm::vec3(aux2, -0.7f, 1.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform7));
                glBindVertexArray(VAO[7]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                if (der < -0.1) {

                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform1));
                    glBindVertexArray(VAO[1]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices2.size());
                }
                else {
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(igual));
                    glBindVertexArray(VAO[1]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices2.size());
                }

            }

            if (tiempo > 0.2) {
                if (aux3 > (0.01)) {
                    aux3 -= 0.01;
                }

                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform5));
                transform5 = glm::translate(transform5, glm::vec3(0.06, 0.0f, 0.0f));
                glBindVertexArray(VAO[3]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                transform6 = glm::translate(transform6, glm::vec3(-0.06, 0.0f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform6));
                glBindVertexArray(VAO[6]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                transform7 = glm::translate(transform7, glm::vec3(aux3, -0.06f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform7));
                glBindVertexArray(VAO[7]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

            }
            if (tiempo > 0.25) {
                if (aux4 > (0.01)) {
                    aux4 -= 0.01;
                }

                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform5));
                transform5 = glm::translate(transform5, glm::vec3(0.06, 0.0f, 0.0f));
                glBindVertexArray(VAO[3]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                transform6 = glm::translate(transform6, glm::vec3(-0.06, 0.0f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform6));
                glBindVertexArray(VAO[6]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                transform7 = glm::translate(transform7, glm::vec3(aux4, -0.06f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform7));
                glBindVertexArray(VAO[7]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

            }
            if (tiempo > 0.3) {
                if (aux5 > (0.01)) {
                    aux5 -= 0.01;
                }

                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform5));
                transform5 = glm::translate(transform5, glm::vec3(0.06, 0.0f, 0.0f));
                glBindVertexArray(VAO[3]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                transform6 = glm::translate(transform6, glm::vec3(-0.06, 0.0f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform6));
                glBindVertexArray(VAO[6]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                transform7 = glm::translate(transform7, glm::vec3(aux5, -0.06f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform7));
                glBindVertexArray(VAO[7]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

            }
            if (tiempo > 0.35 && tiempo < 5.0 ) {
                abajo -= 0.01;
                der2 += 0.01;
                der3 += 0.01;

                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform5));
                transform5 = glm::translate(transform5, glm::vec3(0.06, 0.0f, 0.0f));
                glBindVertexArray(VAO[3]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                transform6 = glm::translate(transform6, glm::vec3(-0.06, 0.0f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform6));
                glBindVertexArray(VAO[6]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                if (abajo > 0.6) {
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform2));
                    glBindVertexArray(VAO[4]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                }
                else {
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(igual2));
                    glBindVertexArray(VAO[4]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                }
                if (der2 < 0.8) {
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform8));
                    glBindVertexArray(VAO[8]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform9));
                    glBindVertexArray(VAO[9]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(abajo1));
                    glBindVertexArray(VAO[8]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(abajo2));
                    glBindVertexArray(VAO[9]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                }
                else {
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(igual3));
                    glBindVertexArray(VAO[8]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(igual4));
                    glBindVertexArray(VAO[9]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(igual5));
                    glBindVertexArray(VAO[8]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(igual6));
                    glBindVertexArray(VAO[9]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                }


            }

            if (tiempo > 0.4) {


                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform5));
                transform5 = glm::translate(transform5, glm::vec3(0.06, 0.0f, 0.0f));
                glBindVertexArray(VAO[3]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                transform6 = glm::translate(transform6, glm::vec3(-0.06, 0.0f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform6));
                glBindVertexArray(VAO[6]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

            }
            if (tiempo > 0.45) {


                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform5));
                transform5 = glm::translate(transform5, glm::vec3(0.06, 0.0f, 0.0f));
                glBindVertexArray(VAO[3]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                transform6 = glm::translate(transform6, glm::vec3(-0.06, 0.0f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform6));
                glBindVertexArray(VAO[6]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

            }
            //termina "setup" ingresa nuestro personaje (el circulo)
            //primero entra por la izquierda
            if (tiempo > 1.12 && tiempo<1.243) {
                per1 += 0.02;
                if (per1 < (-0.82f)) {
                    
                    personaje = glm::translate(personaje, glm::vec3(per1, -0.17f, 0.0f));
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                    glBindVertexArray(VAO[4]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                }
                if (per1 > (-0.82f)) {
                    personaje = glm::translate(personaje, glm::vec3(-0.82f, -0.17f, 0.0f));
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                    glBindVertexArray(VAO[4]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                }
                per2 = per1;
            }
            //se queda quieto contempando
            if (tiempo>1.243 && tiempo<1.6) {
                personaje = glm::translate(personaje, glm::vec3(-0.82f, -0.17f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                per1 = -0.82f;
            }
            //personaje sale por izquerda, en busca de palo
            if (tiempo > 1.6 && tiempo<2.0) {
                
                if (per1 > (-1.8)) {
                    //if (flag3) {//entro una vez para reinciar matriz
                    //    glm::mat4 personaje = glm::mat4(1.0f);
                    //    flag3 = false;
                    //}

                    personaje = glm::translate(personaje, glm::vec3(per1, -0.17f, 0.0f));
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                    glBindVertexArray(VAO[4]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                }
                if (per1 < (-1.8f)) {
                    personaje = glm::translate(personaje, glm::vec3(-1.8f, -0.17f, 0.0f));
                    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                    glBindVertexArray(VAO[4]);
                    glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                }
                per1 -= 0.02;
            }

            //personaje regresa con palo
            if (tiempo > 2.0 && tiempo < 2.15) {
                if (flag3) {
                    per1 = -1.8f;
                    per2 = per1;
                    flag3 = false;
                }
                if (per1 < -0.82f) {
                    per1 += 0.02;
                }
                if (per2 < -0.6f) {
                    per2 += 0.02;
                }
                //if (per1 < -0.82f) {

                palo = glm::translate(palo, glm::vec3(per2, -0.0f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(palo));
                glBindVertexArray(VAO[10]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                personaje = glm::translate(personaje, glm::vec3(per1, -0.17f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());


            }
            //personaje coloca palo (pone en angulo correcto)
            if (tiempo > 2.15 && tiempo<2.63) {
                if (inc < 1.2) {
                    inc += 0.008;
                    //inc2 = inc;
                }
                
                palo = glm::translate(palo, glm::vec3(-0.6f, 0.0f, 0.0f));
                palo = glm::rotate(palo,(float)inc , glm::vec3(0.0f, 0.0f, 1.0f));//
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(palo));
                glBindVertexArray(VAO[10]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());
                
                personaje = glm::translate(personaje, glm::vec3(-0.82f, -0.17f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());


                per1 = -0.82f;
            }
            //esto poorque palo ya se queda fijo por ahora
            if (tiempo > 2.63) {
                palo = glm::translate(palo, glm::vec3(-0.6f, 0.0f, 0.0f));//inc2
                palo = glm::rotate(palo, (float)inc, glm::vec3(0.0f, 0.0f, 1.0f));//
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(palo));
                glBindVertexArray(VAO[10]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());
            }
            //personaje se coloca para subir
            if (tiempo>2.63 && tiempo<2.83) {
                //palo = glm::translate(palo, glm::vec3(-0.6f, 0.0f, 0.0f));//inc2
                //palo = glm::rotate(palo, (float)inc, glm::vec3(0.0f, 0.0f, 1.0f));//
                //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(palo));
                //glBindVertexArray(VAO[10]);
                //glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                personaje = glm::translate(personaje, glm::vec3(per1, -0.17f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                if (per1>-1.18) {
                    per1 -= 0.01;
                }
            }
            //personaje sube
            if (tiempo>2.83 && tiempo<2.96) {
                
                //palo = glm::translate(palo, glm::vec3(-0.6f, 0.0f, 0.0f));//inc2
                //palo = glm::rotate(palo, (float)inc, glm::vec3(0.0f, 0.0f, 1.0f));//
                //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(palo));
                //glBindVertexArray(VAO[10]);
                //glDrawArrays(GL_TRIANGLES, 0, vertices2.size());
                
                personaje = glm::translate(personaje, glm::vec3(diagA, diagB, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                if (diagB < 0.2) {
                    diagA += 0.004;
                    diagB += 0.008;
                }
 
            }
            //Personaje cae 
            if (tiempo > 2.96 &&  tiempo < 3.1 ) {

                //palo = glm::translate(palo, glm::vec3(-0.6f, 0.0f, 0.0f));//inc2
                //palo = glm::rotate(palo, (float)inc, glm::vec3(0.0f, 0.0f, 1.0f));//
                //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(palo));
                //glBindVertexArray(VAO[10]);
                //glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                personaje = glm::translate(personaje, glm::vec3(diagA, diagB, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                if (diagA > -1.18) {
                    diagA -= 0.01;
                    diagB -= 0.02;
                }

            }
            //personaje sube por segunda vez
            if (tiempo > 3.1 && tiempo < 3.3) {

                //palo = glm::translate(palo, glm::vec3(-0.6f, 0.0f, 0.0f));//inc2
                //palo = glm::rotate(palo, (float)inc, glm::vec3(0.0f, 0.0f, 1.0f));//
                //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(palo));
                //glBindVertexArray(VAO[10]);
                //glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                personaje = glm::translate(personaje, glm::vec3(diagA, diagB, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                if (diagB < 0.48) {
                    diagA += 0.004;
                    diagB += 0.008;
                }

            }
            //Personaje cae por segunda vez
            if (tiempo > 3.3 && tiempo< 3.45){// && tiempo < 3.1) {

                //palo = glm::translate(palo, glm::vec3(-0.6f, 0.0f, 0.0f));//inc2
                //palo = glm::rotate(palo, (float)inc, glm::vec3(0.0f, 0.0f, 1.0f));//
                //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(palo));
                //glBindVertexArray(VAO[10]);
                //glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                personaje = glm::translate(personaje, glm::vec3(diagA, diagB, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                if (diagA > -1.18) {
                    diagA -= 0.01;
                    diagB -= 0.02;
                }

            }
            //personaje sube por tercera vez y lo logra
            if (tiempo > 3.45 && tiempo < 4) {

                //palo = glm::translate(palo, glm::vec3(-0.6f, 0.0f, 0.0f));//inc2
                //palo = glm::rotate(palo, (float)inc, glm::vec3(0.0f, 0.0f, 1.0f));//
                //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(palo));
                //glBindVertexArray(VAO[10]);
                //glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                personaje = glm::translate(personaje, glm::vec3(diagA, diagB, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                if (diagB < 0.98) {
                    diagA += 0.004;
                    diagB += 0.008;
                }

            }
            //personaje recorre a la derecha parte roja
            //float aaa;
            if (tiempo > 4 && tiempo < 4.4) {
                personaje = glm::translate(personaje, glm::vec3(diagA, diagB, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                if (diagA < 0.06) {
                    diagA += 0.01;
                    //diagB += 0.008;
                     ///aaa = diagB;
                }
            }
            if (tiempo > 4.4 && tiempo < 4.6) {
                personaje = glm::translate(personaje, glm::vec3(diagA, diagB, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                
            }
            //personaje salta a plataforma (parabola) salto hacia arriba
            if (tiempo > 4.6 && tiempo < 4.75) {
                personaje = glm::translate(personaje, glm::vec3(diagA,   sqrt(diagB), 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                if (diagB < 1.9) {
                    diagA += 0.009;
                    diagB += 0.016;// sqrt(diagA);
//diagB= diagB + sqrt(diagA) ;//ecuacion parabola
                }
            }
            //segunda parte de salto bajabdo
            if (tiempo> 4.75 && diagB >0.45) {
                personaje = glm::translate(personaje, glm::vec3(diagA, sqrt(diagB), 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                if (diagB > 0.45) {
                    diagA += 0.007;
                    diagB -= 0.016;
                }
                //abajoP = diagA;
                abajoP = sqrt(diagB);
            }
            //para mantener unas cosa igual
            if (tiempo > 5.0) {
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform5));
                transform5 = glm::translate(transform5, glm::vec3(0.06, 0.0f, 0.0f));
                glBindVertexArray(VAO[3]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                transform6 = glm::translate(transform6, glm::vec3(-0.06, 0.0f, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform6));
                glBindVertexArray(VAO[6]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());
             }
            //se rompe plataforma, personaje cae junto a segunda esfera
            if (tiempo> 5.0 && diagB <0.45) {
                personaje = glm::translate(personaje, glm::vec3(diagA, abajoP, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(personaje));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                caer = glm::scale(caer, glm::vec3(0.85f));
                caer = glm::translate(caer, glm::vec3(0.8f, caer1, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(caer));
                glBindVertexArray(VAO[4]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                
                caerA = glm::translate(caerA, glm::vec3(0.8f, caer4, 0.0f));//0.5
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(caerA));
                glBindVertexArray(VAO[8]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                
                caerB = glm::translate(caerB, glm::vec3(0.5f, caer2, 0.0f));//0.5
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(caerB));
                glBindVertexArray(VAO[9]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                caerC = glm::translate(caerC, glm::vec3(0.8f, caer3, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(caerC));
                glBindVertexArray(VAO[8]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());
                caerD = glm::translate(caerD, glm::vec3(0.5f, caer3, 0.0f));
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(caerD));
                glBindVertexArray(VAO[9]);
                glDrawArrays(GL_TRIANGLES, 0, vertices3.size());

                if (caer1 > -1.4) {
                    abajoP -= 0.02;
                    caer1 -= 0.01;
                    caer2 -= 0.008;
                    caer3 -= 0.006;
                    caer4 -= 0.007;
                }
                
            }
            //llegan al fondo
            if (caer1< -1.4) {
                //palo1 = glm::scale(palo1, glm::vec3(1.5f));
                palo1 = glm::translate(palo1, glm::vec3(0.0f, 0.4f, 0.0f));
                palo1 = glm::rotate(palo1, 0.78f, glm::vec3(0.0f, 0.0f, 1.0f));//
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(palo1));
                glBindVertexArray(VAO[11]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                palo2 = glm::translate(palo2, glm::vec3(0.0f, 0.4f, 0.0f));
                palo2 = glm::rotate(palo2, 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));//
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(palo2));
                glBindVertexArray(VAO[12]);
                glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

                
            }
           
            
            glfwSwapBuffers(window);
            
        }
            
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(15, VAO);
    glDeleteBuffers(15, VBO);
    glDeleteBuffers(5, EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void rectangulo(float ladoA, float ladoB, float c1,float c2,float c3) {
    
    float aux1 = ladoA / 2.0f;
    float aux2 = ladoB / 2.0f;


    std::vector<glm::vec3> temp;
    temp.push_back(glm::vec3(aux1, aux2, 0.0f));
    temp.push_back(glm::vec3(c1, c2, c3));
    temp.push_back(glm::vec3(-aux1, aux2, 0.0f));
    temp.push_back(glm::vec3(c1, c2, c3));
    temp.push_back(glm::vec3(-aux1, -aux2, 0.0f));
    temp.push_back(glm::vec3(c1, c2, c3));


    
    temp.push_back(glm::vec3(aux1, aux2, 0.0f));
    temp.push_back(glm::vec3(c1, c2, c3));
    temp.push_back(glm::vec3(aux1, -aux2, 0.0f));
    temp.push_back(glm::vec3(c1, c2, c3));
    temp.push_back(glm::vec3(-aux1, -aux2, 0.0f));
    temp.push_back(glm::vec3(c1, c2, c3));
    

    for (int i = 0; i < 7; i++) {
        vertices1.push_back(temp[0]);
        vertices1.push_back(temp[i + 1]);
        vertices1.push_back(temp[i + 2]);
        vertices1.push_back(temp[i + 3]);
        vertices1.push_back(temp[i + 4]);
        vertices1.push_back(temp[i + 5]);


    }


}
void circulo(float radio, int puntos, float c1,float c2, float c3) {
    float angulo = 360.0f / puntos;
    int aux = puntos - 2;
    float anguloActual, x, y, z;

    std::vector<glm::vec3> temp;

    for (int i = 0; i < puntos; i++) {
        //calculo punto
        anguloActual = angulo * i;
        x = radio * cos(glm::radians(anguloActual));// -0.3;// 0.5; si lo quiero mover a la derecha o izq
        y = radio * sin(glm::radians(anguloActual));// +0.2;//si lo quiero mover arriba o abajo
        z = 0.0f;
        //combinas sumas para mover a traves del plano 
        temp.push_back(glm::vec3(x, y, z));//meto punto a vector temporal
        temp.push_back(glm::vec3(c1, c2, c3));//meto color a vector temporal
    }
    for (int i = 0; i < 2*aux-1; i++) { //si solo pongo aux pinta medi circulo
        vertices0.push_back(temp[0]); //metes un punto de tres coord, este nunca cambia 
        vertices0.push_back(temp[i + 1]);//color
        vertices0.push_back(temp[i + 2]);//segundo punto 
        vertices0.push_back(temp[i + 3]);//le das color
        vertices0.push_back(temp[i + 4]);//tercre punto
        vertices0.push_back(temp[i + 5]);//le das color
       // vertices0.push_back(temp[i+1]);
      
    }
}