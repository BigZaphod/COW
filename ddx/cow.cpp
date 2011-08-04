//--------------------------------------------
// COW PROGRAMMING LANGUAGE
// by: BigZaphod sean@fifthace.com
// http://www.bigzaphod.org/cow/
// 
// License: Public Domain
//--------------------------------------------
// Distributed Digestion eXtentions (DDX)
// - added by Bovine Programming Reseach
// - also known as Jason Nordwick.
//--------------------------------------------
#include <vector>
#include <stdio.h>

int const num_stomachs = 7;

typedef std::vector<int> mem_t;
typedef std::vector<mem_t> tract_t;
typedef std::vector<mem_t::iterator> poses_t;

mem_t program;
mem_t::iterator prog_pos;

tract_t memory(num_stomachs);
poses_t mem_poses(num_stomachs);
int stomach;

int register_val;
bool has_register_val = false;

void quit( bool error )
{
    if( error )
    {
        printf( "\nERROR!\n" );
        exit(1);
    }
    
    printf( "\nDone.\n" );
    exit(0);
}

bool exec( int instruction )
{
//    printf( "EXEC: %d\n", instruction );

    switch( instruction )
    {
    // moo
    case 0:
        {
            if( prog_pos == program.begin() )
                quit( true );

            prog_pos--;	// skip previous command.
            int level = 1;
            while( level > 0 )
            {
                if( prog_pos == program.begin() )
                    break;

                prog_pos--;
            
                if( (*prog_pos) == 0 )
                    level++;
                else
                if( (*prog_pos) == 7 )  // look for MOO
                    level--;
            }

            if( level != 0 )
                quit(true);

            return exec( *prog_pos );
        }
    
    // mOo
    case 1:
        if( mem_poses[stomach] == memory[stomach].begin() )
            quit( true );
        else
            mem_poses[stomach]--;
        break;

    // moO
    case 2:
        mem_poses[stomach]++;
        if( mem_poses[stomach] == memory[stomach].end() )
        {
            memory[stomach].push_back(0);
            mem_poses[stomach] = memory[stomach].end();
            mem_poses[stomach]--;
        }
        break;
    
    // mOO    
    case 3:
        if( (*mem_poses[stomach]) == 3 )
            quit( false );
        return exec(*mem_poses[stomach]);
    
    // Moo
    case 4:
        if( (*mem_poses[stomach]) != 0 )
            printf( "%c", *mem_poses[stomach] );
        else
        {
            (*mem_poses[stomach]) = getchar();
            while( getchar() != '\n' );
        }
        break;
    
    // MOo
    case 5:
        (*mem_poses[stomach])--;
        break;
    
    // MoO
    case 6:
        (*mem_poses[stomach])++;
        break;

    // MOO
    case 7:
        if( (*mem_poses[stomach]) == 0 )
        {
            int level = 1;
            int prev = 0;
            prog_pos++;	  // have to skip past next command when looking for next moo.
            if( prog_pos == program.end() )
                break;
            while( level > 0 )
            {
                prev = *prog_pos;
                prog_pos++;
                
                if( prog_pos == program.end() )
                    break;
                
                if( (*prog_pos) == 7 )
                    level++;
                else
                if( (*prog_pos) == 0 )	// look for moo command.
                {
                    level--;
                    if( prev == 7 )
                        level--;
                }
            }
            if( level != 0 )
                quit( true );
        }
        break;
    
    // OOO
    case 8:
        (*mem_poses[stomach]) = 0;
        break;

    // MMM
    case 9:
        if( has_register_val )
            (*mem_poses[stomach]) = register_val;
        else
            register_val = (*mem_poses[stomach]);
        has_register_val = !has_register_val;
        break;

    // OOM
    case 10:
        printf( "%d\n", *mem_poses[stomach] );
        break;
    
    // oom
    case 11:
        {
            char buf[100];
            unsigned int c = 0;
            while( c < sizeof(buf)-1 )
            {
                buf[c] = getchar();
                c++;
                buf[c] = 0;
                
                if( buf[c-1] == '\n' )
                    break;
            }
            // swallow, just in case.
            if( c == sizeof(buf) )
                while( getchar() != '\n' );
            
            (*mem_poses[stomach]) = atoi( buf );

            break;
        }

    // MMm
    case 12:
        {
            stomach--; if(stomach < 0) stomach += num_stomachs;
            break;
        }

    // MmM
    case 13:
        {
            stomach++; if(stomach >= num_stomachs) stomach -= num_stomachs;
            break;
        }

    // Oom
    case 14:
        {
            for( int i=0; i<num_stomachs; ++i )
            {
                if( mem_poses[i] == memory[i].begin() )
                    quit( true );
                else
                    mem_poses[i]--;
            }
            break;
        }

    // oOm
    case 15:
        {
            for( int i=0; i<num_stomachs; ++i )
            {
                mem_poses[i]++;
                if( mem_poses[i] == memory[i].end() )
                {
                    memory[i].push_back(0);
                    mem_poses[i] = memory[i].end();
                    mem_poses[i]--;
                }
            }
            break;
        }
    
    // OoM
    case 16:
        {
            for( int i=0; i<num_stomachs; ++i )
            {
                (*mem_poses[i])--;
            }
            break;
        }

    // oOM
    case 17:
        {
            for( int i=0; i<num_stomachs; ++i)
            {
                (*mem_poses[i])++;
            }
            break;
        }

    // ooo
    case 18:
        {
            for( int i=0; i<num_stomachs; ++i)
            {
                (*mem_poses[i]) = 0;
            }
            break;
        }

    // mmm
    case 19:
        {
            if( has_register_val )
            {
                int weight = 0;
                for( int i=0; i<num_stomachs; ++i)
                {
                    if( *mem_poses[i] > 0 )
                        weight += *mem_poses[i];
                }
                if( weight == 0 )
                {
                    for( int i=0; i<num_stomachs; ++i )
                    {
                        *mem_poses[i] = register_val;
                    }
                } else {
                    int div = register_val / weight;
                    int mod = register_val - div * weight;
                    for( int i=0; i<num_stomachs; ++i )
                    {
                        if( *mem_poses[i] > 0 )
                            *mem_poses[i] = *mem_poses[i] * div;
                        else if( *mem_poses[i] < 0 )
                            *mem_poses[i] = mod * -*mem_poses[i];
                        else
                            *mem_poses[i] = 0;
                    }
                }
            } else {
                int sum = 0;
                for( int i=0; i<num_stomachs; ++i)
                {
                    sum += *mem_poses[i];
                }
                register_val = sum;
            }
            has_register_val = !has_register_val;
            break;
        }

    // bad stuff
    default:
        quit( false );
    };

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
    //int pos = 0; // tola: unused?

    while( !feof(f) )
    {
        int found = 0;
        buf[2] = fgetc( f );

        if(( found = !strncmp( "moo", buf, 3 ) ))
            program.push_back( 0 );
        else if(( found = !strncmp( "mOo", buf, 3 ) ))
            program.push_back( 1 );
        else if(( found = !strncmp( "moO", buf, 3 ) ))
            program.push_back( 2 );
        else if(( found = !strncmp( "mOO", buf, 3 ) ))
            program.push_back( 3 );
        else if(( found = !strncmp( "Moo", buf, 3 ) ))
            program.push_back( 4 );
        else if(( found = !strncmp( "MOo", buf, 3 ) ))
            program.push_back( 5 );
        else if(( found = !strncmp( "MoO", buf, 3 ) ))
            program.push_back( 6 );
        else if(( found = !strncmp( "MOO", buf, 3 ) ))
            program.push_back( 7 );
        else if(( found = !strncmp( "OOO", buf, 3 ) ))
            program.push_back( 8 );
        else if(( found = !strncmp( "MMM", buf, 3 ) ))
            program.push_back( 9 );
        else if(( found = !strncmp( "OOM", buf, 3 ) ))
            program.push_back( 10 );
        else if(( found = !strncmp( "oom", buf, 3 ) ))
            program.push_back( 11 );
        // from here down,  distributed digestion specific calls
        else if(( found = !strncmp( "MMm", buf, 3 ) ))
            program.push_back( 12 );
        else if(( found = !strncmp( "MmM", buf, 3 ) ))
            program.push_back( 13 );
        else if(( found = !strncmp( "Oom", buf, 3 ) ))
            program.push_back( 14 );
        else if(( found = !strncmp( "oOm", buf, 3 ) ))
            program.push_back( 15 );
        else if(( found = !strncmp( "OoM", buf, 3 ) ))
            program.push_back( 16 );
        else if(( found = !strncmp( "oOM", buf, 3 ) ))
            program.push_back( 17 );
        else if(( found = !strncmp( "ooo", buf, 3 ) ))
            program.push_back( 18 );
        else if(( found = !strncmp( "mmm", buf, 3 ) ))
            program.push_back( 19 );
            
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

	printf( "Welcome to COW!\n\nExecuting [%s]...\n\n", argv[1] );

    // init main memory.
    for(int i=0; i<num_stomachs; ++i)
    {
        memory[i].push_back(0);
        mem_poses[i] = memory[i].begin();
    }
    stomach = 0;

    prog_pos = program.begin();
    while( prog_pos != program.end() )
        if( !exec( *prog_pos ) )
            break;

    quit( false );

	return 0;
}


