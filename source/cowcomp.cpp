//--------------------------------------------
// COW PROGRAMMING LANGUAGE COMPILER
// by: BigZaphod sean@fifthace.com
// http://www.bigzaphod.org/cow/
// 
// License: Public Domain
//--------------------------------------------
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#define COMPILER	"g++"
#define FLAGS		"-O3 -x c++"
#define NAME_FLAG	"-o "
#define OUTPUT_EXEC "cow.out"
#define OUTPUT_CPP	"cow.out.cpp"


//#define PRETTY(s)	fprintf( output, "\t\t\t// %s\n", s );
#define PRETTY(s)	


typedef std::vector<int> mem_t;
mem_t program;
mem_t::iterator prog_pos;
FILE* output;

int moocount(0);
int MOOcount(0);


void quit()
{
    printf( "Compile error.  Invalid source code.\n" );
    exit(1);
}

bool compile( int instruction, bool advance )
{
    switch( instruction )
    {
    // moo
    case 0:
        {
            int level = 1;
            int num = MOOcount + 1;
            mem_t::iterator t = prog_pos;

            t--;   // skip past previous command when searching for MOO.
            if( t != program.begin() )
            {
                if((*t) == 7 )
                    num--;

                while( level > 0 )
                {
                    if( t == program.begin() )
                        break;

                    t--;
            
                    if( (*t) == 0 )
                        level++;
                    else
                    if( (*t) == 7 )  // look for MOO
                    {
                        level--;
                        num--;
                    }
                }
            }
            if( level != 0 && advance )
                quit();
            else if( level != 0 )
            {
                fprintf( output, "rterr();" );
                break;
            }

            moocount++;
            fprintf( output, "goto M%d;", num );
            fprintf( output, "m%d:", moocount );
            PRETTY( "moo" );
        }
        break;

    
    // mOo
    case 1:
        fprintf( output, "if(p==m.begin()){rterr();}else{p--;}" );
        PRETTY( "mOo" );
        break;

    // moO
    case 2:
        fprintf( output, "p++; if(p==m.end()){m.push_back(0);p=m.end();p--;}" );
        PRETTY( "moO" );
        break;
    
    // mOO    
    case 3:
        // I think it should be possible to build a switch statement here and then
        // use the compile function itself to fill in the possibilities.
//        printf( "NOT IMPLEMENTED: mOO\n\n" );
//        quit();
        fprintf( output, "switch(*p){" );
        fprintf( output, "case 0:{" ); compile( 0, false ); fprintf( output, "}break;" );
        fprintf( output, "case 1:{" ); compile( 1, false ); fprintf( output, "}break;" );
        fprintf( output, "case 2:{" ); compile( 2, false ); fprintf( output, "}break;" );
        fprintf( output, "case 4:{" ); compile( 4, false ); fprintf( output, "}break;" );
        fprintf( output, "case 5:{" ); compile( 5, false ); fprintf( output, "}break;" );
        fprintf( output, "case 6:{" ); compile( 6, false ); fprintf( output, "}break;" );
        fprintf( output, "case 7:{" ); compile( 7, false ); fprintf( output, "}break;" );
        fprintf( output, "case 8:{" ); compile( 8, false ); fprintf( output, "}break;" );
        fprintf( output, "case 9:{" ); compile( 9, false ); fprintf( output, "}break;" );
        fprintf( output, "case 10:{" ); compile( 10, false ); fprintf( output, "}break;" );
        fprintf( output, "case 11:{" ); compile( 11, false ); fprintf( output, "}break;" );
        fprintf( output, "default:{goto x;}};" );
        PRETTY( "mOO" );
        break;
    
    // Moo
    case 4:
        fprintf( output, "if((*p)!=0){putchar(*p);}else{(*p)=getchar();while(getchar()!='\\n');}" );
        PRETTY( "Moo" );
        break;
    
    // MOo
    case 5:
        fprintf( output, "(*p)--;" );
        PRETTY( "MOo" );
        break;
    
    // MoO
    case 6:
        fprintf( output, "(*p)++;" );
        PRETTY( "MoO" );
        break;

    // MOO
    case 7:
        {
            int level = 1;
            int num = moocount;
            int prev = 0;
            mem_t::iterator t = prog_pos;
            t++;	  // have to skip past next command when looking for next moo.

            if( t != program.end() )
            {
                if( (*t) == 0 )
                    num++;

                while( level > 0 )
                {
                    prev = *t;
                    t++;
                
                    if( t == program.end() )
                        break;
                
                    if( (*t) == 7 ) // look for MOO command.
                        level++;
                    else
                    if( (*t) == 0 )	// look for moo command.
                    {
                        if( prev == 7 )
                            level--;
                
                        level--;
                        num++;
                    }
                
                    if( level == 0 )
                        break;
                }
            }
            if( advance && level != 0 )
                quit();
            else if( level != 0 )
            {
                fprintf( output, "rterr();" );
                break;
            }
            
            MOOcount++;
            fprintf( output, "M%d:", MOOcount );
            fprintf( output, "if(!(*p))goto m%d;", num );
            PRETTY( "MOO" );
        }
        break;
    
    // OOO
    case 8:
        fprintf( output, "(*p)=0;" );
        PRETTY( "OOO" );
        break;

    // MMM
    case 9:
        fprintf( output, "if(h){(*p)=r;}else{r=(*p);}h=!h;" );
        PRETTY( "MMM" );
        break;

    // OOM
    case 10:
        fprintf( output, "printf(\"%%d\\n\",*p);" );
        PRETTY( "OOM" );
        break;
    
    // oom
    case 11:
        fprintf( output, "char b[100];int c=0;" );
        fprintf( output, "while(c<sizeof(b)-1){b[c]=getchar();c++;b[c]=0;if(b[c-1]=='\\n')break;}" );
        fprintf( output, "if(c==sizeof(b))while(getchar()!='\\n');(*p)=atoi(b);" );
        PRETTY( "oom" );
        break;

    // bad stuff
    default:
        return false;
    };

    if( advance )
        prog_pos++;

    return true;
}


int main( int argc, char** argv )
{
	if( argc < 2 )
	{
		printf( "Usage: %s program.cow\n\n", argv[0] );
		exit( 1 );
	}

	FILE* f = fopen( argv[1], "rb" );

	if( f == NULL )
	{
		printf( "Cannot open source file [%s].\n", argv[1] );
        exit( 1 );
	}

    char buf[3];
    memset( buf, 0, 3 );
    int pos = 0;

    while( !feof(f) )
    {
        int found = 0;
        buf[2] = fgetc( f );

        if( found = !strncmp( "moo", buf, 3 ) )
            program.push_back( 0 );
        else if( found = !strncmp( "mOo", buf, 3 ) )
            program.push_back( 1 );
        else if( found = !strncmp( "moO", buf, 3 ) )
            program.push_back( 2 );
        else if( found = !strncmp( "mOO", buf, 3 ) )
            program.push_back( 3 );
        else if( found = !strncmp( "Moo", buf, 3 ) )
            program.push_back( 4 );
        else if( found = !strncmp( "MOo", buf, 3 ) )
            program.push_back( 5 );
        else if( found = !strncmp( "MoO", buf, 3 ) )
            program.push_back( 6 );
        else if( found = !strncmp( "MOO", buf, 3 ) )
            program.push_back( 7 );
        else if( found = !strncmp( "OOO", buf, 3 ) )
            program.push_back( 8 );
        else if( found = !strncmp( "MMM", buf, 3 ) )
            program.push_back( 9 );
        else if( found = !strncmp( "OOM", buf, 3 ) )
            program.push_back( 10 );
        else if( found = !strncmp( "oom", buf, 3 ) )
            program.push_back( 11 );
            
        if( found )
        {
            memset( buf, 0, 3 );
        }
        else
        {
            buf[0] = buf[1];
            buf[1] = buf[2];
            buf[2] = 0;
        }
    }

	fclose( f );

	printf( "Compiling [%s]...\n", argv[1] );

    // init main memory.
    /*
    memory.push_back( 0 );
    mem_pos = memory.begin();
    */
    
    output = fopen( "cow.out.cpp", "wb" );
    fprintf( output, "#include <stdio.h>\n" );
    fprintf( output, "#include <vector>\n" );
    fprintf( output, "typedef std::vector<int> t_;t_ m;t_::iterator p;\n" );
    fprintf( output, "bool h;int r;\n" );
    fprintf( output, "void rterr(){puts(\"Runtime error.\\n\");}\n" );
    fprintf( output, "int main(int a,char** v){\n" );
    fprintf( output, "m.push_back(0);p=m.begin();h=false;\n" );

    prog_pos = program.begin();
    while( prog_pos != program.end() )
        if( !compile( *prog_pos, true ) )
        {
            printf( "ERROR!\n" );
            break;
        }
        
    fprintf( output, "x:return(0);}\n" );        
    fclose( output );

    printf( "C++ source code: cow.out.cpp\n" );

    #ifdef COMPILER
        std::string path( (const char*)COMPILER );
        path.append( " " );
        path.append( (const char*)NAME_FLAG );
        path.append( " " );
        path.append( (const char*)OUTPUT_EXEC );
        path.append( " " );
        path.append( (const char*)FLAGS );
        path.append( " " );
        path.append( (const char*)OUTPUT_CPP );
        if( system( path.c_str() ) )
            printf( "\n\nCould not compile.  Possible causes:  C++ compiler is not installed, not in path, or not named '%s' or there is a bug in this compiler.\n\n", COMPILER );
        else
            printf( "Executable created: cow.out\n" );
    #endif

	return 0;
}


