

1、指令遵循之前的格式：

        0 - 电机选择   1 - F4/F3   2 - 频高        3 - 频低
        4 - 步高       5 - 步低    6 - 指令流水号  7- 电机运行方向
        
2、地址101遵循之前的格式：

    a、  10 - 俯仰电机   20 - 摇摆头电机
    b、 俯仰电机：
           方    向：  1 - 抬头      0 - 低头
           限位状态：  1 - 上限位    2 - 下限位      0 - 没碰到限位
           行    程：
           频率范围：
    c、摇摆头电机：
           方    向：  1 - 左摆      0 - 右摆
           限位状态：  1 - 左限位    2 - 右限位      0 - 没碰到限位
           行    程：
           频率范围：
3、地址102中：
    a、  30 - 控制腰部电机     90 - 控制头部偏航
    b、腰部电机：
           方    向：  1 - 抬腰      0 - 下腰
           限位状态：  1 - 上限位    2 - 下限位      0 - 没碰到限位
           行    程：
           频率范围：
    c、偏航电机：
           方    向：  1 - 左转      0 - 右转
           限位状态：  1 - 左限位    2 - 右限位      0 - 没碰到限位
           行    程：  
           频率范围：
