if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
            play_cai_phone= true;
            play_cai_book= true;
            first_t_phone = currentFrame;
            first_t_book = currentFrame;
         }
         if(play_cai_phone){
            if(delta_phone<duracao_caida){
                delta_phone = currentFrame - first_t_phone;
                if(delta_phone >0.0f){
                    float val_y = (delta_phone * 0.3f);
                    model2 = glm::translate(model2, glm::vec3(0.0f,-val_y, 0.0f)); 
                    valor_queda_phone+=val_y;
                }
            }else{
                
                model2 = glm::translate(model2, glm::vec3(0.0f,valor_queda_phone, 0.0f)); 
                delta_phone =0.0f;
                first_t_phone = currentFrame;
                valor_queda_phone =0.0f;
                model2[3][0] = min_x + rand() * (max_x - min_x) / RAND_MAX; 
            }
         }
         if(play_cai_book){
            if(delta_book<duracao_caida){
                delta_book = currentFrame - first_t_book;
                if(delta_book >0.0f){
                    float val_y = (delta_book * 0.3f);
                    model3 = glm::translate(model3, glm::vec3(0.0f,-val_y, 0.0f)); 
                    valor_queda_book+=val_y;
                }
            }else{
                
                model3 = glm::translate(model3, glm::vec3(0.0f,valor_queda_book, 0.0f)); 
                delta_book =0.0f;
                first_t_book = currentFrame;
                valor_queda_book =0.0f;
                model3[3][0] = min_x + rand() * (max_x - min_x) / RAND_MAX; 
            }
         }