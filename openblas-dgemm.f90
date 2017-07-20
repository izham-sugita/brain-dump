!how to compile:
!Dynamic linking,
! $gfortran -o filename filename.f90 -lopenblas -lpthread
!Static linking
! $gfortran -o filename filename.f90 /your/path/to/libopenblas.a -lpthread
program blas1
  implicit none
  real(8), allocatable, dimension(:) :: a, b, c
  real(8), allocatable, dimension(:,:) :: matA, matB, matC
  real(8) :: alpha, beta
  real(8) :: error
  
  integer :: i, j, imax, jmax
  integer, dimension(8) :: values
  integer :: seed
  integer :: index

  character(len=1) :: transa, transb

  imax = 1024
  jmax = 1024

  call date_and_time(VALUES=values) !values(8) = milisecs of the second
  seed = values(8)
  call srand(seed) !not a std implementation, but i like it better.
  !print*, values
  print*, rand(), rand(), rand()
  
  allocate(a(imax*jmax))
  allocate(b(imax*jmax))
  allocate(c(imax*jmax))
  allocate(matA(imax,jmax))
  allocate(matB(imax,jmax))
  allocate(matC(imax,jmax))

  !initiating array
  print*, 'Initiating arrays....'
  do j = 1, jmax
     do i = 1, imax
        index = (j-1)*imax + i
        a(index) = rand()
        b(index) = rand()
        c(index) = 0.0
     end do
  end do

  do j = 1, jmax
     do i = 1, imax
        index = (j-1)*imax + i
        matA(i,j) = a(index)
        matB(i,j) = b(index)
        matC(i,j) = 0.0
     end do
  end do
  
  alpha = 1.0
  beta = 0.0
  transa = 'N'
  transb = 'N'
  call dgemm(transa,transb,imax,jmax,imax,alpha,a,imax,b,imax,beta,c,imax)

  print*, 'Checking for correctness....'
  matC = matmul(matA, matB)

  i = 10
  j = 10
  index = (j-1)*imax + i
  print*, 'matC(',i,',',j,') = ', matC(i,j)
  print*, 'c(',index,') = ', c(index)

  error = 0.0
  do j = 1, jmax
     do i = 1, imax
        index = (j-1)*imax + i
        error = error + abs(matC(i,j) - c(index))
     end do
  end do
  print*, error
  
  print*, 'Deallocating arrays....'
  deallocate(a,b,c)
  deallocate(matA,matB,matC)
  
end program blas1
