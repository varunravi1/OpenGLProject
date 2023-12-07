#ifndef MAIN_MENU


#include "glad/glad.h"
#include <GLFW/glfw3.h>
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shader_s.h"
#include <iostream>
#endif
#include "UNO.h"
#include <string>


void uno_framebuffer_size_callback(GLFWwindow* window, int width, int height);
void uno_processInput(GLFWwindow *window);
int unomainloop();
void uno_display_card(int color, int ability, int number);
// int main();
// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
char random_start_card[] = "/home/team11/Desktop/Code/Graphics Code/Uno_img/blue-0.png";
char new_card[] = "/home/team11/Desktop/Code/Graphics Code/Uno_img/green-2.png";
std::string current_card = "/home/team11/Desktop/Code/Graphics Code/Uno_img/green-2.png";
bool card_played = false;

// int main ()
// {
//     unomainloop();
// }

void uno_display_card(int color, int ability, int number)
{
    current_card = "/home/team11/Desktop/Code/Graphics Code/Uno_img/";
    switch(ability)
    {
        case 0:
        switch(color)
        {
            case 1:
            current_card = current_card + "red-";
            break;
            case 2: 
            current_card = current_card + "green-";
            break;
            case 3:
            current_card = current_card + "blue-";
            break;
            case 4:
            current_card = current_card + "yellow-";
            break;
        }
        switch(number)
        {
            case 0:
            current_card = current_card + "0.png";
            break;
            case 1:
            current_card = current_card + "1.png";
            break;
            case 2:
            current_card = current_card + "2.png";
            break;
            case 3:
            current_card = current_card + "3.png";
            break;
            case 4:
            current_card = current_card + "4.png";
            break;
            case 5:
            current_card = current_card + "5.png";
            break;
            case 6:
            current_card = current_card + "6.png";
            break;
            case 7:
            current_card = current_card + "7.png";
            break;
            case 8:
            current_card = current_card + "8.png";
            break;
            case 9:
            current_card = current_card + "9.png";
            break;
        }
        break;
        case 1:
        switch(color)
        {
            case 1:
            current_card = current_card + "red-d.png";
            break;
            case 2: 
            current_card = current_card + "green-d.png";
            break;
            case 3:
            current_card = current_card + "blue-d.png";
            break;
            case 4:
            current_card = current_card + "yellow-d.png";
            break;
        }
        break;
        case 2:
        switch(color)
        {
            case 1:
            current_card = current_card + "red-r.png";
            break;
            case 2: 
            current_card = current_card + "green-r.png";
            break;
            case 3:
            current_card = current_card + "blue-r.png";
            break;
            case 4:
            current_card = current_card + "yellow-r.png";
            break;
        }
        break;
        case 3:
        switch(color)
        {
            case 1:
            current_card = current_card + "red-s.png";
            break;
            case 2: 
            current_card = current_card + "green-s.png";
            break;
            case 3:
            current_card = current_card + "blue-s.png";
            break;
            case 4:
            current_card = current_card + "yellow-s.png";
            break;
        }
        break;
        case 4:
        current_card = current_card + "wild-four.png";
        break;
        case 5:
        current_card = current_card + "wild-color.png";
        break;
        default:
        std::cout << "Invalid ability" << std::endl;
    }
    card_played = true;
}
int unomainloop()
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
    glfwSetFramebufferSizeCallback(window, uno_framebuffer_size_callback);

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
    unsigned char *backdata = stbi_load("/home/team11/Desktop/Code/Graphics Code/UNO_background.png", &backwidth, &backheight, &backnrChannels, 0);
    //std::cout << leftnrChannels;
    if (backdata)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, backwidth, backheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, backdata);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(backdata);








    //LEFT CARD




    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float leftvertices[] = {
        // positions          // colors           // texture coords
        -0.12f,  0.31f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
        -0.12f, -0.31f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.38f, -0.31f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.38f,  0.31f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    // unsigned int indices[] = {  
    //     0, 1, 3, // first triangle
    //     1, 2, 3  // second triangle
    // };
    unsigned int leftVBO, leftVAO, leftEBO;
    glGenVertexArrays(1, &leftVAO);
    glGenBuffers(1, &leftVBO);
    glGenBuffers(1, &leftEBO);

    glBindVertexArray(leftVAO);

    glBindBuffer(GL_ARRAY_BUFFER, leftVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(leftvertices), leftvertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, leftEBO);
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
    unsigned int lefttexture;
    glGenTextures(1, &lefttexture);
    glBindTexture(GL_TEXTURE_2D, lefttexture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int leftwidth, leftheight, leftnrChannels;
    stbi_set_flip_vertically_on_load(1);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *leftdata = stbi_load(current_card.c_str(), &leftwidth, &leftheight, &leftnrChannels, 0);
    //std::cout << leftnrChannels;
    if (leftdata)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, leftwidth, leftheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, leftdata);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(leftdata);





    //RIGHT CARD






    float rightvertices[] = {
        // positions          // colors           // texture coords
        0.38f,  0.31f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0f, // top right
        0.38f, -0.31f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        0.12f, -0.31f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        0.12f,  0.31f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    // unsigned int indices[] = {  
    //     0, 1, 3, // first triangle
    //     1, 2, 3  // second triangle
    // };
    unsigned int rightVBO, rightVAO, rightEBO;
    glGenVertexArrays(1, &rightVAO);
    glGenBuffers(1, &rightVBO);
    glGenBuffers(1, &rightEBO);

    glBindVertexArray(rightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, rightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rightvertices), rightvertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rightEBO);
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
    unsigned int righttexture;
    glGenTextures(1, &righttexture);
    glBindTexture(GL_TEXTURE_2D, righttexture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int rightwidth, rightheight, rightnrChannels;
    stbi_set_flip_vertically_on_load(1);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *rightdata = stbi_load("/home/team11/Desktop/Code/Graphics Code/Uno_img/uno-back.png", &rightwidth, &rightheight, &rightnrChannels, 0);
    //std::cout << nrChannels;
    if (rightdata)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rightwidth, rightheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, rightdata);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(rightdata);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        uno_processInput(window);

        // renderS
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, backtexture);
        ourShader.use();
        glBindVertexArray(backVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
        if(card_played == true)
        {

            int width, height, nrChannels;
            unsigned char *playedData = stbi_load(current_card.c_str(), &width, &height, &nrChannels, 0);
            if(playedData)
            {
                glBindTexture(GL_TEXTURE_2D, lefttexture);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, playedData);
                glGenerateMipmap(GL_TEXTURE_2D);   
            }   
            else 
            {
                std::cout << "Failed to load newcard texture" << std::endl;

            }      

            

        }
        // bind Texture
        glBindTexture(GL_TEXTURE_2D, lefttexture);
        ourShader.use();
        glBindVertexArray(leftVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 


        // bind Texture
        glBindTexture(GL_TEXTURE_2D, righttexture);
        // render container
        ourShader.use();
        glBindVertexArray(rightVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &leftVAO);
    glDeleteBuffers(1, &leftVBO);
    glDeleteBuffers(1, &leftEBO);
    glDeleteVertexArrays(1, &rightVAO);
    glDeleteBuffers(1, &rightVBO);
    glDeleteBuffers(1, &rightEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void uno_processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        uno_display_card(1,0,7);
        //std::cout << "Pressed 1 \n";
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void uno_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}