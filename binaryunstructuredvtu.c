/*
This program writes an unstructured data to .vtu binary format(appended)
The technique used here was refered from file VTKFormats.f90
This code was successful.
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{

  //setting up arrays
  int ndim   = 3; //dimension
  int nnos   = 4; // nodes count
  int nnoel  = 3; // number of nodes per element
  int nel    = 2; // number of elements
  
  //coordinate array
  //float xyz[nnos][ndim]
   float xyz[4][3] ={
    {0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {1.0, 1.0, 0.0},
    {0.0, 1.0, 0.0}
  };

  // vector qty array
  //float vec[nnos][ndim] ={
   float vec[4][3] ={
    {0.0, 0.0, 1.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, 1.0}
  };

  //scalar qty array
  // float scalar[nnos]
  float scalar[4] = {0.0, 1.0, 2.0, 1.0};

  //connectivity array
  //int ien[nel][nnoel] = {
  int ien[2][3] = {
    {0,1,2},
    {3,0,2}
  };

  //vtk default
  int element_type = 5; 

  //preparing variables
  int var;
  int nbytes_scalar = nnos*sizeof(float);
  int nbytes_vec    = ndim*nnos*sizeof(float);
  int nbytes_xyz    = ndim*nnos*sizeof(float);
  int nbytes_ien    = nnoel*nel*sizeof(int);
  int nbytes_offset = nel*sizeof(int);
  int nbytes_etype  = nel*sizeof(int);

  //calculating offsets
  var = sizeof(int);
  int off0 = 0;
  int off1 = off0 + var + nbytes_scalar;
  int off2 = off1 + var + nbytes_vec;
  int off3 = off2 + var + nbytes_xyz;
  int off4 = off3 + var + nbytes_ien;
  int off5 = off4 + var + nbytes_offset;

  FILE *fp;
  fp = fopen("ctest_xml_vtu.vtu","wb");
  fprintf(fp,"<?xml version=\"1.0\"?>\n");
  fprintf(fp,"<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n");    
  fprintf(fp,"<UnstructuredGrid>\n");
  fprintf(fp,"<Piece NumberOfPoints=\"%d\" NumberOfCells=\"%d\">\n", nnos, nel);
  fprintf(fp,"<PointData>\n");
  fprintf(fp,"<DataArray type=\"Float32\" Name=\"scalars\" format=\"appended\" offset=\"%d\" />\n", off0); 
  fprintf(fp,"<DataArray type=\"Float32\" Name=\"vectors\" NumberOfComponents=\"3\" format=\"appended\" offset=\"%d\" /> \n",off1);
  fprintf(fp,"</PointData>\n");
  fprintf(fp,"<CellData>  </CellData>\n");
  fprintf(fp,"<Points>\n");
  fprintf(fp,"<DataArray type=\"Float32\" Name=\"coordinates\" NumberOfComponents=\"3\" format=\"appended\" offset=\"%d\" /> \n", off2);
  fprintf(fp, "</Points>\n");
  fprintf(fp, "<Cells>\n");
  fprintf(fp,"<DataArray type=\"Int32\" Name=\"connectivity\" format=\"appended\" offset=\"%d\" /> \n",off3);
  fprintf(fp,"<DataArray type=\"Int32\" Name=\"offsets\" format=\"appended\" offset=\"%d\" /> \n ", off4);
  fprintf(fp,"<DataArray type=\"Int32\" Name=\"types\" format=\"appended\" offset=\"%d\" /> \n" , off5);
  fprintf(fp,"</Cells> \n");
  fprintf(fp,"</Piece> \n");
  fprintf(fp,"</UnstructuredGrid> \n");
  fprintf(fp,"<AppendedData encoding=\"raw\"> \n");
  fprintf(fp,"_");

  //write(ivtk) nbytes_scal  , (scal(i),i=1,nnos)   !scalar data
  fwrite(&nbytes_scalar, sizeof(int),1,fp);
  for(int i=0; i<nnos; ++i){
    float temp = scalar[i];
    fwrite(&temp, sizeof(float),1,fp);
  }

  //  write(ivtk) nbytes_vec   , ((vec(i,j),i=1,ndim),j=1,nnos) !vector data
  fwrite(&nbytes_vec, sizeof(int), 1, fp);
  for(int i=0; i<nnos; ++i){
    for(int j=0; j<ndim; ++j){
      float temp = vec[i][j];
      fwrite(&temp, sizeof(float), 1, fp);
    }
  }

  //  write(ivtk) nbytes_xyz   , ((xyz(i,j),i=1,ndim),j=1,nnos) !coordinate data
  fwrite(&nbytes_xyz, sizeof(int),1,fp);
  for(int i=0; i<nnos; ++i){
    for(int j=0; j<ndim; ++j){
      float temp = xyz[i][j];
      fwrite(&temp, sizeof(float),1,fp);
    }
  }

  //  write(ivtk) nbytes_ien   , ((ien(i,j),i=1,nnoel),j=1,nel) !connectivity data
  fwrite(&nbytes_ien, sizeof(int),1,fp);
  //int ien[nel][nnoel] = {
  for(int i=0; i<nel; ++i){
    for(int j=0; j<nnoel; ++j){
      int temp = ien[i][j];
      fwrite(&temp,sizeof(int),1,fp);
    }
  }

  //  write(ivtk) nbytes_offset, (i,i=nnoel,nnoel*nel,nnoel)    !offsets data
  fwrite(&nbytes_offset,sizeof(int),1,fp);
  for(int i=nnoel; i<=nnoel*nel; i+=nnoel){
    int temp = i;
    fwrite(&temp,sizeof(int),1,fp);
    printf("%d\t", i);
  };
  printf("\n");

  //  write(ivtk) nbytes_etype , (etype,i=1,nel)                !element type; vtk-specified
  fwrite(&nbytes_etype,sizeof(int), 1, fp);
  for(int i=0; i<nel; ++i){
    fwrite(&element_type,sizeof(int),1,fp);
  }
  
  fclose(fp);
}
