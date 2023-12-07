#include "glad/glad.h"
#include <GLFW/glfw3.h>
#define MAIN_MENU
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shader_s.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "UNO.h"


//////////////////////////////////////////////////////////////


//char random_start_card[] = "/home/team11/Desktop/Code/Graphics Code/Uno_img/blue-0.png";





void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void menunumber(int);
int menunum = 1;
int game_sel_num = 1;
bool drawn = false;
int signal = 0;
// void menuselect(int num)
// {
//     menunum = num;
// }
void menunumber(int num)
{
    menunum = num;
    drawn = false;
}
void gameselect(int num)
{
    game_sel_num = num;
    drawn = false;
}

// static const char first_screen[] = "/home/team11/Desktop/Code/Graphics Code/Main Menu/main_menu_background_red_menu.png";
// static const char select_game[] = "/home/team11/Desktop/Code/Graphics Code/Main Menu/main_menu_background_white_menu.png";

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "UNO", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("v.glsl", "f.glsl"); 

    //BACKGROUND

        // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float backvertices[] = {
        // positions          // colors           // texture coords
        1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
        1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int backVBO, backVAO, backEBO;
    glGenVertexArrays(1, &backVAO);
    glGenBuffers(1, &backVBO);
    glGenBuffers(1, &backEBO);

    glBindVertexArray(backVAO);

    glBindBuffer(GL_ARRAY_BUFFER, backVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(backvertices), backvertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, backEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int backtexture;
    glGenTextures(1, &backtexture);
    glBindTexture(GL_TEXTURE_2D, backtexture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int backwidth, backheight, backnrChannels;
    stbi_set_flip_vertically_on_load(1);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *backdata = stbi_load("/home/team11/Desktop/Code/Graphics Code/Main Menu/main_menu_background_red_menu.png", &backwidth, &backheight, &backnrChannels, 0);
    //std::cout << leftnrChannels;
    if (backdata)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, backwidth, backheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, backdata);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(backdata);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    float game_select_vertices[] = {
        // positions          // colors           // texture coords
        1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
        1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int selVBO, selVAO, selEBO;
    glGenVertexArrays(1, &selVAO);
    glGenBuffers(1, &selVBO);
    glGenBuffers(1, &selEBO);

    glBindVertexArray(selVAO);

    glBindBuffer(GL_ARRAY_BUFFER, selVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(game_select_vertices), game_select_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, selEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int seltexture;
    glGenTextures(1, &seltexture);
    glBindTexture(GL_TEXTURE_2D, seltexture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int selwidth, selheight, selnrChannels;
    stbi_set_flip_vertically_on_load(1);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *seldata = stbi_load("/home/team11/Desktop/Code/Graphics Code/Main Menu/main_menu_background_white_menu.png", &selwidth, &selheight, &selnrChannels, 0);
    //std::cout << leftnrChannels;
    if (seldata)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, selwidth, selheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, seldata);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(seldata);



    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float red_diamond_2[] = {
        // positions          // colors           // texture coords
        0.35f,  0.68f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
        0.35f, 0.53f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        0.25f, 0.53f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        0.25f,  0.68f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int dimVBO2, dimVAO2, dimEBO2;
    glGenVertexArrays(1, &dimVAO2);
    glGenBuffers(1, &dimVBO2);
    glGenBuffers(1, &dimEBO2);

    glBindVertexArray(dimVAO2);

    glBindBuffer(GL_ARRAY_BUFFER, dimVBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(red_diamond_2), red_diamond_2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dimEBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int dimtexture2;
    glGenTextures(1, &dimtexture2);
    glBindTexture(GL_TEXTURE_2D, dimtexture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int dimwidth2, dimheight2, dimnrChannels2;
    stbi_set_flip_vertically_on_load(1);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *dimdata2 = stbi_load("/home/team11/Desktop/Code/Graphics Code/Main Menu/cursor_red.png", &dimwidth2, &dimheight2, &dimnrChannels2, 0);
    //std::cout << leftnrChannels;
    if (dimdata2)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimwidth2, dimheight2, 0, GL_RGBA, GL_UNSIGNED_BYTE, dimdata2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(dimdata2);
































    //////////////////////////////////////////////////////////////////////////////////


    float red_diamond_1[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
        0.5f, 0.35f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        0.4f, 0.35f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        0.4f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int dimVBO, dimVAO, dimEBO;
    glGenVertexArrays(1, &dimVAO);
    glGenBuffers(1, &dimVBO);
    glGenBuffers(1, &dimEBO);

    glBindVertexArray(dimVAO);

    glBindBuffer(GL_ARRAY_BUFFER, dimVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(red_diamond_1), red_diamond_1, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dimEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // load and create a texture 
    // -------------------------
    unsigned int dimtexture;
    glGenTextures(1, &dimtexture);
    glBindTexture(GL_TEXTURE_2D, dimtexture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int dimwidth, dimheight, dimnrChannels;
    stbi_set_flip_vertically_on_load(1);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *dimdata = stbi_load("/home/team11/Desktop/Code/Graphics Code/Main Menu/cursor_white.png", &dimwidth, &dimheight, &dimnrChannels, 0);
    //std::cout << leftnrChannels;
    if (dimdata)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimwidth, dimheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, dimdata);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(dimdata);


////////////////////////////////////////////////////////////////////////////UNO//////////////////////////////////////////////////////////////////////////////////////
   
   
   
   
   
   
   
   
    // float uno_backvertices[] = {
    //     // positions          // colors           // texture coords
    //     1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
    //     1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    //     -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    //     -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    // };

    // unsigned int uno_backVBO, uno_backVAO, uno_backEBO;
    // glGenVertexArrays(1, &uno_backVAO);
    // glGenBuffers(1, &uno_backVBO);
    // glGenBuffers(1, &uno_backEBO);

    // glBindVertexArray(uno_backVAO);

    // glBindBuffer(GL_ARRAY_BUFFER, uno_backVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(uno_backvertices), uno_backvertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uno_backEBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // // position attribute
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    // // color attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    // // texture coord attribute
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);


    // // load and create a texture 
    // // -------------------------
    // unsigned int uno_backtexture;
    // glGenTextures(1, &uno_backtexture);
    // glBindTexture(GL_TEXTURE_2D, uno_backtexture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // // set the texture wrapping parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // // set texture filtering parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // // load image, create texture and generate mipmaps
    // int uno_backwidth, uno_backheight, uno_backnrChannels;
    // stbi_set_flip_vertically_on_load(1);
    // // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    // unsigned char *uno_backdata = stbi_load("/home/team11/Desktop/Code/Graphics Code/UNO_background.png", &uno_backwidth, &uno_backheight, &uno_backnrChannels, 0);
    // //std::cout << leftnrChannels;
    // if (uno_backdata)
    // {
    //     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, uno_backwidth, uno_backheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, uno_backdata);
    //     glGenerateMipmap(GL_TEXTURE_2D);
    // }
    // else
    // {    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    //     std::cout << "Failed to load texture" << std::endl;
    // }
    // stbi_image_free(uno_backdata);






    // //LEFT CARD




    // // set up vertex data (and buffer(s)) and configure vertex attributes
    // // ------------------------------------------------------------------
    // float leftvertices[] = {
    //     // positions          // colors           // texture coords
    //     -0.12f,  0.31f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
    //     -0.12f, -0.31f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    //     -0.38f, -0.31f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    //     -0.38f,  0.31f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    // };
    // // unsigned int indices[] = {  
    // //     0, 1, 3, // first triangle
    // //     1, 2, 3  // second triangle
    // // };
    // unsigned int leftVBO, leftVAO, leftEBO;
    // glGenVertexArrays(1, &leftVAO);
    // glGenBuffers(1, &leftVBO);
    // glGenBuffers(1, &leftEBO);

    // glBindVertexArray(leftVAO);

    // glBindBuffer(GL_ARRAY_BUFFER, leftVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(leftvertices), leftvertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, leftEBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // // position attribute
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    // // color attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    // // texture coord attribute
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);


    // // load and create a texture 
    // // -------------------------
    // unsigned int lefttexture;
    // glGenTextures(1, &lefttexture);
    // glBindTexture(GL_TEXTURE_2D, lefttexture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // // set the texture wrapping parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // // set texture filtering parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // // load image, create texture and generate mipmaps
    // int leftwidth, leftheight, leftnrChannels;
    // stbi_set_flip_vertically_on_load(1);

    // unsigned char *leftdata = stbi_load("/home/team11/Desktop/Code/Graphics Code/Uno_img/blue-0.png", &leftwidth, &leftheight, &leftnrChannels, 0);
    // //std::cout << leftnrChannels;
    // if (leftdata)
    // {
    //     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, leftwidth, leftheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, leftdata);
    //     glGenerateMipmap(GL_TEXTURE_2D);
    // }
    // else
    // {
    //     std::cout << "Failed to load texture" << std::endl;
    // }
    // stbi_image_free(leftdata);





    // //RIGHT CARD






    // float rightvertices[] = {
    //     // positions          // colors           // texture coords
    //     0.38f,  0.31f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
    //     0.38f, -0.31f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    //     0.12f, -0.31f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    //     0.12f,  0.31f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    // };
    // // unsigned int indices[] = {  
    // //     0, 1, 3, // first triangle
    // //     1, 2, 3  // second triangle
    // // };
    // unsigned int rightVBO, rightVAO, rightEBO;
    // glGenVertexArrays(1, &rightVAO);
    // glGenBuffers(1, &rightVBO);
    // glGenBuffers(1, &rightEBO);

    // glBindVertexArray(rightVAO);

    // glBindBuffer(GL_ARRAY_BUFFER, rightVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(rightvertices), rightvertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rightEBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // // position attribute
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    // // color attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    // // texture coord attribute
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);


    // // load and create a texture 
    // // -------------------------
    // unsigned int righttexture;
    // glGenTextures(1, &righttexture);
    // glBindTexture(GL_TEXTURE_2D, righttexture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // // set the texture wrapping parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // // set texture filtering parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // // load image, create texture and generate mipmaps
    // int rightwidth, rightheight, rightnrChannels;
    // stbi_set_flip_vertically_on_load(1);
    // // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    // unsigned char *rightdata = stbi_load("/home/team11/Desktop/Code/Graphics Code/Uno_img/uno-back.png", &rightwidth, &rightheight, &rightnrChannels, 0);
    // //std::cout << nrChannels;
    // if (rightdata)
    // {
    //     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rightwidth, rightheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, rightdata);
    //     glGenerateMipmap(GL_TEXTURE_2D);
    // }
    // else
    // {
    //     std::cout << "Failed to load texture" << std::endl;
    // }
    // stbi_image_free(rightdata);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////MAINLOOP//////////////////////////////////////////////////////////////////////
    //bool drawn = false;
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // render
        // ------
        switch(menunum)
        {
            case 1:
            glBindTexture(GL_TEXTURE_2D, backtexture);
            ourShader.use();
            glBindVertexArray(backVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);     
            glBindBuffer(GL_ARRAY_BUFFER, dimVBO2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(red_diamond_2), red_diamond_2, GL_STATIC_DRAW);
            glBindTexture(GL_TEXTURE_2D, dimtexture2);
            ourShader.use();
            glBindVertexArray(dimVAO2);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);       
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
            case 2:
            glBindTexture(GL_TEXTURE_2D, seltexture);
            ourShader.use();
            glBindVertexArray(selVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            switch(game_sel_num)
            {
                case 1: 
                glBindBuffer(GL_ARRAY_BUFFER, dimVBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(red_diamond_1), red_diamond_1, GL_STATIC_DRAW);
                glBindTexture(GL_TEXTURE_2D, dimtexture);    
                ourShader.use();
                glBindVertexArray(dimVAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
                if(signal == 1)
                {
                    glfwSetWindowShouldClose(window, true);
                    //start_uno(window);
                }
                break;
                case 2:
                if(drawn == false)
                {
                    float white_diamond_temp[] = {
                    // positions          // colors           // texture coords
                    0.5f,  0.36f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
                    0.5f, 0.21f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                    0.4f, 0.21f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
                    0.4f,  0.36f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
                    };
                    glBindBuffer(GL_ARRAY_BUFFER, dimVBO);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(white_diamond_temp), white_diamond_temp, GL_STATIC_DRAW);
                    drawn = true;
                }
                glBindTexture(GL_TEXTURE_2D, dimtexture);
                ourShader.use();
                glBindVertexArray(dimVAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);       
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                case 3:
                if(drawn == false)
                {
                    float white_diamond_temp_1[] = {
                    // positions          // colors           // texture coords
                    0.5f,  0.22f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
                    0.5f, 0.07f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                    0.4f, 0.07f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
                    0.4f,  0.22f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
                    };
                    glBindBuffer(GL_ARRAY_BUFFER, dimVBO);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(white_diamond_temp_1), white_diamond_temp_1, GL_STATIC_DRAW);
                    drawn = true;
                }
                glBindTexture(GL_TEXTURE_2D, dimtexture);
                ourShader.use();
                glBindVertexArray(dimVAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);       
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            }


            break;
            case 3:
            glBindTexture(GL_TEXTURE_2D, backtexture);
            ourShader.use();
            glBindVertexArray(backVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
            if(drawn == false)
            {
                float red_diamond_temp[] = {
                // positions          // colors           // texture coords
                0.35f,  -0.12f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
                0.35f, -0.27f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                0.25f, -0.27f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
                0.25f,  -0.12f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
                };
                // for(int i = 0; i < 4; ++i)
                // {
                //     red_diamond_2[i * 8 + 1] += -0.8f;
                //     std::cout << red_diamond_2[i * 8 + 1] << std::endl;
                // }
                glBindBuffer(GL_ARRAY_BUFFER, dimVBO2);
                glBufferData(GL_ARRAY_BUFFER, sizeof(red_diamond_temp), red_diamond_temp, GL_STATIC_DRAW);
                drawn = true;
            }
            //std::cout << red_diamond_2 << std::endl;                    GLFW_KEY_ESCAPE = GLFW_PRESS;
            glBindTexture(GL_TEXTURE_2D, dimtexture2);
            ourShader.use();
            glBindVertexArray(dimVAO2);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);       
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
            case 4:
            glBindTexture(GL_TEXTURE_2D, backtexture);
            ourShader.use();
            glBindVertexArray(backVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
            if(drawn == false)
            {
                float red_diamond_temp_1[] = {
                // positions          // colors           // texture coords
                0.35f,  -0.33f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
                0.35f, -0.48f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                0.25f, -0.48f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
                0.25f,  -0.33f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
                };
                glBindBuffer(GL_ARRAY_BUFFER, dimVBO2);
                glBufferData(GL_ARRAY_BUFFER, sizeof(red_diamond_temp_1), red_diamond_temp_1, GL_STATIC_DRAW);
                drawn = true;
            }              

            glBindTexture(GL_TEXTURE_2D, dimtexture2);
            ourShader.use();
            glBindVertexArray(dimVAO2);           // glBindVertexArray(dimVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);       
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
            case 5:
            glBindTexture(GL_TEXTURE_2D, backtexture);
            ourShader.use();
            glBindVertexArray(backVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
            if(drawn == false)
            {
                float red_diamond_temp_2[] = {
                // positions          // colors           // texture coords
                0.35f,  -0.55f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
                0.35f, -0.70f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                0.25f, -0.70f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
                0.25f,  -0.55f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
                };
                glBindBuffer(GL_ARRAY_BUFFER, dimVBO2);
                glBufferData(GL_ARRAY_BUFFER, sizeof(red_diamond_temp_2), red_diamond_temp_2, GL_STATIC_DRAW);
                drawn = true;
            }

            glBindTexture(GL_TEXTURE_2D, dimtexture2);
            ourShader.use();
            glBindVertexArray(dimVAO2);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);       
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }


        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        // glBindTexture(GL_TEXTURE_2D, backtexture);
        // ourShader.use();
        // glBindVertexArray(backVAO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 



        // glBindTexture(GL_TEXTURE_2D, newtexture);
        // // render container
        // glm::mat4 transform = glm::mat4(1.0f);
        // transform = glm::translate(transform, glm::vec3(0.0f,0.0f,0.0f));

        // ourShader.use();
        // unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        // glBindVertexArray(newVAO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &backVAO);
    glDeleteBuffers(1, &backVBO);
    glDeleteBuffers(1, &backEBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    if(signal == 1)
    {
        unomainloop();
    }
    return 0;

}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        menunumber(1);
        //std::cout << "Pressed 1 \n";
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        menunumber(2);
        gameselect(1);
        //std::cout << "Pressed 1 \n";
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        menunumber(3);
        //drawn = false;
        //std::cout << "Pressed 1 \n";
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        menunumber(4);
        //drawn = false;
        //std::cout << "Pressed 1 \n";
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        menunumber(5);
        //drawn = false;
        //std::cout << "Pressed 1 \n";
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        gameselect(2);
        //drawn = false;
        //std::cout << "Pressed 1 \n";
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        gameselect(3);
        //drawn = false;
        //std::cout << "Pressed 1 \n";
    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        
        signal = 1; 
        //drawn = false;
        //std::cout << "Pressed 1 \n";
    }

    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
