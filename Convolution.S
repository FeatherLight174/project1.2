.import input.S

.text
main:
    # Size getting
    lw a4, image_width
    lw a5, image_length
    lw a2, kernel_width
    lw a3, kernel_length
    addi s1, x0, 4

    # Result-size getting
    sub t0, a4, a2
    addi t0, t0, 1          #t0: result_width
    sub t1, a5, a3
    addi t1, t1, 1          #t1: result_length

    # load address
    la t2, image
    la t3, kernel

    # image width loop
    li t4, 0                       #t4: conv_row_number
    conv_row_loop:
    li t5, 0                       #t5: conv_col_number
    blt t4, t0, conv_col_loop      #go from row to row
    j conv_end

    # image length loop
     
    conv_col_loop:
    blt t5, t1, conv_compute       #go frem col to col
    #
    addi a1, x0, 10
    li a0, 11
    ecall                          #print \n
    #
    addi t4, t4, 1  
    j conv_row_loop

    conv_compute:
    li t6, 0

    # kernel loop
    li s7, 0                       #s7: ker_row_number
    kernel_row_loop:
    li s8, 0                       #s8: ker_col_number
    blt s7, a2, kernel_col_loop
    addi t5, t5, 1  
    
    #
    add a1, x0, t6                 #print t6(result)
    li a0, 1
    ecall
    addi a1, x0, 32                #print space
    li a0, 11
    ecall
    #
    
    j conv_col_loop

      
    kernel_col_loop:
    blt s8, a3, calculating

    addi s7, s7, 1  
    j kernel_row_loop

    calculating:
    # address calculating
    
    
    add s9, s7, t4                  #image address
    mul s9, s9, a5
    add s9, s9, t5
    add s9, s9, s8
    mul s9, s9, s1
    add s9, s9, t2
    
    mul s10, s7, a3                 #kernel address
    add s10, s10, s8
    mul s10, s10, s1
    add s10, s10, t3

    lw s11, 0(s9)
    lw s6, 0(s10)

    # calculating
    mul s11, s11, s6
    add t6, t6, s11                 #calculating
    
    
    
    

    addi s8, s8, 1  
    j kernel_col_loop

    conv_end:
    li a0, 10
    ecall
