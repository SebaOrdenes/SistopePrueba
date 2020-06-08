#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <jpeglib.h>

void escribirImagen(int alto,int ancho,int numeroImagen,unsigned char ** matrizGrayBinarizada)
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    char nombre[20];
    unsigned char * matrizGrayBinarizadaAux;
    matrizGrayBinarizadaAux=(unsigned char *)malloc(alto*ancho*3*sizeof(unsigned char));
    sprintf(nombre,"salida_%i.jpg",numeroImagen);
    int contador=0;
    for(int i=0;i<alto;i++){
        for(int j=0;j<ancho;j++){
            matrizGrayBinarizadaAux[contador]=matrizGrayBinarizada[i][j];
            contador++;
        }
    }
    /* this is a pointer to one row of image data */
    JSAMPROW row_pointer[1];
    FILE *outfile = fopen( nombre, "wb" );
   
    if ( !outfile )
    {
        printf("Error opening output jpeg file %s\n!", nombre);
        exit(EXIT_FAILURE);
    }
    cinfo.err = jpeg_std_error( &jerr );
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    /* Setting the parameters of the output file here */
    cinfo.image_width = ancho;
    cinfo.image_height = alto;
    cinfo.input_components = 1;
    cinfo.in_color_space = JCS_GRAYSCALE; //img->color_space;
    /* default compression parameters, we shouldn't be worried about these */
    jpeg_set_defaults( &cinfo );
    /* Now do the compression .. */
    jpeg_start_compress( &cinfo, TRUE );
    /* like reading a file, this time write one row at a time */
    while( cinfo.next_scanline < cinfo.image_height )
    {
        row_pointer[0]= &matrizGrayBinarizadaAux[ cinfo.next_scanline * cinfo.image_width*cinfo.input_components];
        jpeg_write_scanlines( &cinfo, row_pointer, 1 );
    }
    /* similar to read file, clean up after we're done compressing */
    jpeg_finish_compress( &cinfo );
    jpeg_destroy_compress( &cinfo );
    fclose( outfile );
    /* success code is 1! */
    
}