// to calculate theta
float cal_theta(float curr_pos[],float target_pos[]){
  float latLength = distance(curr_pos[1], curr_pos[0], target_pos[1], curr_pos[0], 1); 
  float lonLength = distance(curr_pos[1],  curr_pos[0],  curr_pos[1], target_pos[0], 1);
  if(latLength == 0)
    latLength == 0.0001; 
  if(lonLength == 0)
    lonLength == 0.0001; 
  float theta = degrees(atan(lonLength/latLength));
  return theta; //output for diff or for pure pursuit
}
/*
float Kalman_filter (Ts,C,Y,R,){
       %declare the matrices
    A[6][6] = [  {1, 0, 0, Ts,  0,  0},
                 {0, 1, 0,  0, Ts,  0},
                 {0, 0, 1,  0,  0, Ts},
                 {0, 0, 0,  1,  0,  0},
                 {0, 0, 0,  0,  1,  0},
                 {0, 0, 0,  0,  0,  1}};
    C[6][6] = [  {0, 0, 0,  0,  0,  0},
                 {0, 0, 0,  0,  0,  0},
                 {0, 0, 1,  0,  0, Ts},
                 {0, 0, 0,  0,  0,  0},
                 {0, 0, 0,  0,  0,  0},
                 {0, 0, 0,  0,  0,  1}};
    H = eye(6);
    U[6][1] = {{     {0},
                     {0},
                {0.0001},
                     {0},
                     {0},
                 0.0001}}*-1;
    V = {{1},
         {1},
         {1},
         {1},
         {1},
         {1}}*1;
    W = {{0},
         {0},
         {0},
         {0},
         {0},
         {0}};
    %error variance
    Q = {{1, 0, 0, 0, 0, 0},
         {0, 1, 0, 0, 0, 0},
         {0, 0, 1, 0, 0, 0},
         {0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 1, 0},
         {0, 0, 0, 0, 0, 1}};
    %persistent P Xhat Q;
    if isempty(Xhat)
        %initial states
        Xhat = [1;1;1;1;1;1];
        P = eye(6);
    end
        
    %Calculating the state estimate
    Xhat = A*Xhat+W;  
    %X_ = Xhat;
    %Calcualting the process covariance matrix
    P = A*P*A' + Q;    
    
    %Kalman Gain
    K = P*H'/(H*P*H' + R);
    
    %Calculating the Measurement
    Yhat = C*Y + U;
    %Calculating the Measurement Resd
    err = Yhat - Xhat;
    %using kalman gain calculating the Xhat and P
    Xhat = Xhat + K*err;
    Xout = Xhat;
    P = (eye(size(K,1))- K*H)*P;
    Pout = P;

}
   */
