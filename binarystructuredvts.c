#include<stdio.h>
#include<stdlib.h>

int main()
{

/*

Sample for the ascii file data

<?xml version="1.0"?>
<VTKFile type="StructuredGrid" version="0.1" byte_order="LittleEndian" compressor="vtkZLibDataCompressor">
  <StructuredGrid WholeExtent="0 1 0 2 0 3">
  <Piece Extent="0 1 0 2 0 3">
    <PointData Scalars="Scalars_">
      <DataArray type="Int16" Name="Scalars_" format="ascii" RangeMin="0" RangeMax="6">
        0 1 1 2 2 3
        1 2 2 3 3 4
        2 3 3 4 4 5
        3 4 4 5 5 6
      </DataArray>
    </PointData>
    <CellData>
    </CellData>
    <Points>
      <DataArray type="Float32" Name="Array 0x85412e8" NumberOfComponents="3" format="ascii" RangeMin="0" RangeMax="3.7416573868">
        0 0 0 1 0 0
        0 1 0 1 1 0
        0 2 0 1 2 0
        0 0 1 1 0 1
        0 1 1 1 1 1
        0 2 1 1 2 1
        0 0 2 1 0 2
        0 1 2 1 1 2
        0 2 2 1 2 2
        0 0 3 1 0 3
        0 1 3 1 1 3
        0 2 3 1 2 3
      </DataArray>
    </Points>
  </Piece>
  </StructuredGrid>
</VTKFile>

*/

  int scalar[24] = {0,1,1,2,2,3,1,2,2,3,3,4,2,3,3,4,4,5,3,4,4,5,5,6}; //read_by_column

  float array[3*24]={0,0,0, 1,0,0, 0,1,0, 1,1,0,0,2,0,1,2,0,0,0,1,1,0,1,0,1,1,1,1,1,0,2,1,
      1,2,1,0,0,2,1,0,2,0,1,2,1,1,2,0,2,2,1,2,2,0,0,3,1,0,3,0,1,3,1,1,3,0,2,3,1,2,3 }; 
  
int ndim = 3;
int ix = 2;
int iy = 3;
int iz = 4;

int off0;
int off1;

int var = sizeof(int);

int NumberOfElements = ix*iy*iz;
 
int nbytes_vec    = ndim*NumberOfElements*sizeof(float);
int nbytes_scalar = NumberOfElements*sizeof(int);

off0 = 0;
off1 = off0 + var + nbytes_scalar;

FILE *fp;
fp = fopen("structured.vts","wb");
fprintf(fp,"<?xml version=\"1.0\"?> \n");
//fprintf(fp,"<VTKFile type=\"StructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\" header_type=\"UInt64\"> \n");
//header_type=\"UInt64\" <- this header cause wrong data reading, why? bug? stupid software!
 
fprintf(fp,"<VTKFile type=\"StructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\"> \n");
fprintf(fp,"<StructuredGrid WholeExtent=\"0 %d 0 %d 0 %d\"> \n",ix-1, iy-1, iz-1);
fprintf(fp,"<Piece Extent=\"0 %d 0 %d 0 %d\"> \n", ix-1, iy-1, iz-1);

 fprintf(fp,"<PointData Scalars=\"Scalars_\"> \n"); //OK!
//fprintf(fp,"<PointData> \n");                     //OK!

 fprintf(fp,"<DataArray type=\"Int16\" Name=\"Scalars_\" format=\"appended\" offset=\"%d \"  RangeMin=\"0\" RangeMax=\"6\"> \n", off0);
fprintf(fp,"</DataArray> \n");
fprintf(fp,"</PointData> \n");
fprintf(fp,"<CellData>");
fprintf(fp,"</CellData>");

fprintf(fp,"<Points> \n");
// fprintf(fp,"<DataArray type=\"Float32\" Name=\"Array\" NumberOfComponents=\"3\" format=\"appended\" offset=\"%d \" RangeMin=\"0\" RangeMax=\"3.7416573868\"> \n", off1); //Ok to fix range, if you know the value.

 fprintf(fp,"<DataArray type=\"Float32\" Name=\"Array\" NumberOfComponents=\"3\" format=\"appended\" offset=\"%d\" > \n", off1);
fprintf(fp," </DataArray> \n");
fprintf(fp,"</Points>\n");
  
fprintf(fp,"</Piece> \n");
fprintf(fp,"</StructuredGrid> \n");

fprintf(fp,"<AppendedData encoding=\"raw\"> \n");
fprintf(fp,"_");
//raw data goes here

 fwrite(&nbytes_scalar, sizeof(int),1,fp);
  for(int i=0; i<NumberOfElements; ++i){
    int temp = scalar[i];
    fwrite(&temp, sizeof(int),1,fp);
  }
    
  fwrite(&nbytes_vec, sizeof(int), 1, fp);
  for(int i=0; i<NumberOfElements; ++i){  
    float temp = array[3*i]; //x-value
      fwrite(&temp, sizeof(float), 1, fp);
      temp = array[3*i+1];   //y-value
      fwrite(&temp, sizeof(float), 1, fp);
      temp = array[3*i+2];   //z-value
      fwrite(&temp, sizeof(float), 1, fp);
  }
 
  fprintf(fp,"\n"); 
  fprintf(fp,"</AppendedData> \n");
  fprintf(fp,"</VTKFile>");

fclose(fp);

}
