#ifndef __F247_PARSE01_CPP__
#define __F247_PARSE01_CPP__



enum /* The following values are returned negative for error reasons */
    {
    F247_PARSE01_ERR_ok=0,
    F247_PARSE01_ERR_invalid,
    F247_PARSE01_ERR_datarange,
    F247_PARSE01_ERR_addrrange,
    F247_PARSE01_ERR_datasize,
    F247_PARSE01_ERR_MAX
    };


#include "f247_simple_types.cpp"


#if __INCLUDE_LEVEL__ == 0
#include <stdio.h>
#include <stdlib.h>
static const char* F247_PARSE01_errstrings[F247_PARSE01_ERR_MAX]=
    {
    "ok",
    "invalid",
    "datarange",
    "addrrange",
    "datasize"
    };
#endif // if __INCLUDE_LEVEL__ == 0



/* - - - - - - - L E G A C Y  F U N C T I O N S - - - - - - - - - - - - */



void F247_PARSE01_check_result(int result)
#if __INCLUDE_LEVEL__ == 0
    {
    if(0>result)
        {
        if(-result<F247_PARSE01_ERR_MAX)
            {
            fprintf(stderr,"\nF247_PARSE01 error: %s . Exit.",F247_PARSE01_errstrings[-result]);
            exit(-1);
            }
            else
            fprintf(stderr,"\nF247_PARSE01 error: UNKNOWN . Exit.");
        }
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0




/*
 * Input data: hexadecimal values without '0x' or '$' or '#' or 'h' decorations,
 *             separated with white characters
 *             the number of digits (including all zeros) determines the value size,
 *             which is returned
 * Returns:  * on success: positive number of digits read (1 .. 8)
 *           * on EOF: 0
 *           * on error: negative
 */
int F247_PARSE01_fget_hex32(FILE* fp, U32* ptr)
#if __INCLUDE_LEVEL__ == 0
    {
    int result=0;
    int got;
    *ptr=0;
    while(1)
        {
        got=fgetc(fp);
        switch(got)
            {
            case 0:
            case EOF:
                return -F247_PARSE01_ERR_ok;
            case 'a' ... 'f':
            case 'A' ... 'F':
            case '0' ... '9':
                if(result>=8)
                    return -F247_PARSE01_ERR_datarange;
                result++;
                (*ptr)<<=4;
                break;
            default:
                return -F247_PARSE01_ERR_invalid;
            case 0x01 ... 0x20:
                if(result)
                    return -F247_PARSE01_ERR_ok;
                break;
            }
        switch(got)
            {
            case 'a' ... 'f':
                (*ptr)|=(U32)(got-(int)'a'+10);
                break;
            case 'A' ... 'F':
                (*ptr)|=(U32)(got-(int)'A'+10);
                break;
            case '0' ... '9':
                (*ptr)|=(U32)(got-(int)'0');
                break;
            }
        }
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



/*
 * Input data: hexadecimal values without '0x' or '$' or '#' or 'h' decorations,
 *             separated with white characters,
 *             the number of digits (including all zeros) determines the value size,
 *             which is returned.
 *             A value larger than one byte is swapped for LE reasons.
 *             The ':' immediately (without spaces) after a value make it the new starting address in the area.
 *             The default starting address in the area is 0.
 * Returns:  * on success: 0
 *           * on EOF: 0
 *           * on error: negative
 */
int F247_PARSE01_fget_le_memory(FILE* fp, U08* area_ptr, int area_size)
#if __INCLUDE_LEVEL__ == 0
    {
    int result;
    int address=0;
    U32 got=0;
    while(1)
        {
        result=F247_PARSE01_fget_hex32(fp, &got);
        if(0<result)
            {
            if(1&result)
                result++; /* must be even for whole bytes */
            while(result)
                {
                if(address>=area_size)
                    return -F247_PARSE01_ERR_addrrange;
                *(area_ptr+address)=(U08)(got&0xFF);
                address++;
                result-=2;
                got>>=8;
                }
            }
            else
            {
            if(0==result)
                return address;
            return result;
            }
        }/* while(1)*/
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



/* - - - - - - - M O D E R N  F U N C T I O N S - - - - - - - - - - - - */



/*
 * To be used in place of char
 */
typedef char F247_PARSE01_char;



/*
 * Defines the group of characters to check if a character belongs to the group
 */
typedef F247_PARSE01_char* F247_PARSE01_group; /* The array of at least 2 items must be declared */
/* The first (0th) item is the opcode. Next items depend on the opcode */
/* The OPCODE's cardinal codes: */
#define F247_PARSE01_GROPC_null            0  /* As an opcode it means 'do nothing and exit', also it ends a list or a string */
#define F247_PARSE01_GROPC_white          'W' /* Embedded check 'white character' */
#define F247_PARSE01_GROPC_eol            'E' /* Embedded check 'end of line' */
#define F247_PARSE01_GROPC_fromto         'R' /* Check from an ASCII character (including it) to another ASCII character (including it) */
#define F247_PARSE01_GROPC_single         'S' /* Check the single character */
#define F247_PARSE01_GROPC_list           'L' /* Check a list of characters ending with F247_PARSE01_GROPC_null */



#define F247_PARSE01_CHAR_eos '\0' /* terminating character */



/*
 * Input data: * The pointer to the character being checked,
 *             * The group of characters.
 * Returns:    * when the character belongs to the group: 1,
 *             * otherwise: 0
 */
int F247_PARSE01_check_char_membership(F247_PARSE01_char* Cptr, F247_PARSE01_group group)
#if __INCLUDE_LEVEL__ == 0
    {
    int Ind=0;
    while(1)
        {
        switch(group[Ind])
            {
            default:
            case F247_PARSE01_GROPC_null:
                return 0;
            case F247_PARSE01_GROPC_white:
                if((*Cptr==' ')||(*Cptr=='\t'))
                    return 1;
                break;
            case F247_PARSE01_GROPC_eol:
                if((*Cptr=='\r')||(*Cptr=='\n'))
                    return 1;
                break;
            case F247_PARSE01_GROPC_fromto:
                Ind+=2;
                if((*Cptr>=group[Ind-1])&&(*Cptr<=group[Ind-0]))
                    return 1;
                break;
            case F247_PARSE01_GROPC_single:
                Ind+=1;
                if(*Cptr==group[Ind-0])
                    return 1;
                break;
            case F247_PARSE01_GROPC_list:
                do  {
                    Ind++;
                    if(*Cptr==group[Ind])
                        return 1;
                    }
                    while(F247_PARSE01_GROPC_null!=group[Ind]);
                break;
            }
        Ind++;
        }
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



/*
 * Gets the string from the file. The string is bounded with two separators groups: _omit before and _stop after
 * Returns:    * 0:        when EOL or _stop separator occured before any gathering
 *             * positive: number of characters gathered, not including the ending F247_PARSE01_CHAR_eos
 *             * negative: on error, eg. insufficient buffer size
 *             ! In the buffer_ptr, AFTER the ending F247_PARSE01_CHAR_eos, the separator is appended which has stopped gathering.
 */
int F247_PARSE01_fget_anything
    (
    FILE* fp,
    F247_PARSE01_char* buffer_ptr,
    int buffer_size,
    F247_PARSE01_group separator_omit,
    F247_PARSE01_group separator_stop,
    unsigned* line_ptr
    )
#if __INCLUDE_LEVEL__ == 0
    {
    int result=0;
    int got;
    F247_PARSE01_char C;
    while(1)
        {
        got=fgetc(fp);
        C=(F247_PARSE01_char)got;
        if((0==got)||(EOF==got))
            break;
        if('\n'==C)
            {
            if(NULL!=line_ptr)
                (*line_ptr)++;
            }
        if(result) /* result is also the buffer index and indicates that buffer is not empty */
            {
            if(F247_PARSE01_check_char_membership(&C,separator_stop))
                break;
            if(result+2>=buffer_size) /* +2 because the place for ending and separator must be kept */
                {
                buffer_ptr[buffer_size-1]=F247_PARSE01_CHAR_eos;
                buffer_ptr[buffer_size-2]=F247_PARSE01_CHAR_eos;
                return -F247_PARSE01_ERR_datasize;
                }
            }
            else
            {
            if(F247_PARSE01_check_char_membership(&C,separator_omit))
                continue;
            if(F247_PARSE01_check_char_membership(&C,separator_stop))
                break;
            }
        buffer_ptr[result]=C;
        result++;
        }
    buffer_ptr[result  ]=F247_PARSE01_CHAR_eos;
    buffer_ptr[result+1]=C;
    return result;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



/*
 * Skips the string from the file. The string's end is bounded with the separators group: _stop after
 * Returns:    * 0:        when EOL or _stop separator occured before any gathering
 *             * positive: number of characters gathered
 *             * negative: on error
 */
int F247_PARSE01_fskip_anything
    (
    FILE* fp,
    F247_PARSE01_group separator_stop,
    unsigned* line_ptr
    )
#if __INCLUDE_LEVEL__ == 0
    {
    int result=0;
    int got;
    F247_PARSE01_char C;
    while(1)
        {
        got=fgetc(fp);
        C=(F247_PARSE01_char)got;
        if((0==got)||(EOF==got))
            break;
        if('\n'==C)
            {
            if(NULL!=line_ptr)
                (*line_ptr)++;
            }
        if(F247_PARSE01_check_char_membership(&C,separator_stop))
            break;
        result++;
        }
    return result;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



/*
 * Removes preceding and trailing chars from a string in the buffer: _beg before and _end after
 * Returns:    * positive: number of characters remainig in the buffer, not including the ending F247_PARSE01_CHAR_eos
 *             * negative: on error, eg. insufficient buffer size
 */
int F247_PARSE01_scrape
    (
    F247_PARSE01_char* buffer_ptr,
    int buffer_size,
    F247_PARSE01_group separator_beg,
    F247_PARSE01_group separator_end
    )
#if __INCLUDE_LEVEL__ == 0
    {
    int i,Beg,End;
    for(i=0; (i!=buffer_size) && ( F247_PARSE01_check_char_membership(buffer_ptr+i,separator_beg)); i++)
        ;
    if((Beg=i)==buffer_size)
        return -F247_PARSE01_ERR_datasize;
    for(   ; (i!=buffer_size) && (!F247_PARSE01_check_char_membership(&buffer_ptr[i],separator_end)); i++)
        ;
    if((End=i)==buffer_size)
        return -F247_PARSE01_ERR_datasize;
    for(i=Beg;i!=End;i++)
        buffer_ptr[i-Beg]=buffer_ptr[i];
    buffer_ptr[End-Beg]=F247_PARSE01_CHAR_eos;
    return (End-Beg);
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0




int F247_PARSE01_get_U32dec(F247_PARSE01_char* string_ptr, U32* data_ptr)
#if __INCLUDE_LEVEL__ == 0
    {
    int pos_beg=0;
    int pos_end=0;
    *data_ptr=0;
    while(string_ptr[pos_end]!=F247_PARSE01_CHAR_eos)
        pos_end++;
    if(0==pos_end)
        return -F247_PARSE01_ERR_invalid;
    pos_end--;
    if((0!=pos_end)&&(('d'==string_ptr[pos_end])||('D'==string_ptr[pos_end])))
        pos_end--;
    if(('#'==string_ptr[pos_beg])||('$'==string_ptr[pos_beg]))
        pos_beg++;
        else
        {
        if(('0'==string_ptr[pos_beg])&&(('d'==string_ptr[pos_beg+1])||('D'==string_ptr[pos_beg+1])))
            pos_beg+=2;
        }
    if(pos_beg>pos_end)
        return -F247_PARSE01_ERR_invalid;
    if(pos_beg+9<pos_end)
        return -F247_PARSE01_ERR_datarange;
    for(;pos_beg<=pos_end;pos_beg++)
        {
        (*data_ptr)*=10;
        switch(string_ptr[pos_beg])
            {
            case '0' ... '9':
                (*data_ptr)+=(U32)(string_ptr[pos_beg]-'0');
                break;
            default:
                return -F247_PARSE01_ERR_invalid;
            }
        }
    return -F247_PARSE01_ERR_ok;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



int F247_PARSE01_get_S32dec(F247_PARSE01_char* string_ptr, S32* data_ptr)
#if __INCLUDE_LEVEL__ == 0
    {
    int pos_beg=0;
    int pos_end=0;
    int neg=0;
    *data_ptr=0;
    while(string_ptr[pos_end]!=F247_PARSE01_CHAR_eos)
        pos_end++;
    if(0==pos_end)
        return -F247_PARSE01_ERR_invalid;
    pos_end--;
    if((0!=pos_end)&&(('d'==string_ptr[pos_end])||('D'==string_ptr[pos_end])))
        pos_end--;
    if('-'==string_ptr[pos_beg])
        {
        neg^=1;
        pos_beg++;
        }
        else
        {
        if('+'==string_ptr[pos_beg])
            pos_beg++;
        }
    if(('#'==string_ptr[pos_beg])||('$'==string_ptr[pos_beg]))
        pos_beg++;
        else
        {
        if(('0'==string_ptr[pos_beg])&&(('d'==string_ptr[pos_beg+1])||('D'==string_ptr[pos_beg+1])))
            pos_beg+=2;
        }
    if('-'==string_ptr[pos_beg])
        {
        neg^=1;
        pos_beg++;
        }
        else
        {
        if('+'==string_ptr[pos_beg])
            pos_beg++;
        }
    if(pos_beg>pos_end)
        return -F247_PARSE01_ERR_invalid;
    if(pos_beg+9<pos_end)
        return -F247_PARSE01_ERR_datarange;
    for(;pos_beg<=pos_end;pos_beg++)
        {
        (*data_ptr)*=10;
        switch(string_ptr[pos_beg])
            {
            case '0' ... '9':
                (*data_ptr)+=(S32)(string_ptr[pos_beg]-'0');
                break;
            default:
                return -F247_PARSE01_ERR_invalid;
            }
        }
    (*data_ptr)*=(neg ? -1L : 1L);
    return -F247_PARSE01_ERR_ok;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



int F247_PARSE01_get_U32hex(F247_PARSE01_char* string_ptr, U32* data_ptr)
#if __INCLUDE_LEVEL__ == 0
    {
    int pos_beg=0;
    int pos_end=0;
    *data_ptr=0;
    while(string_ptr[pos_end]!=F247_PARSE01_CHAR_eos)
        pos_end++;
    if(0==pos_end)
        return -F247_PARSE01_ERR_invalid;
    pos_end--;
    if((0!=pos_end)&&(('h'==string_ptr[pos_end])||('H'==string_ptr[pos_end])))
        pos_end--;
    if(('#'==string_ptr[pos_beg])||('$'==string_ptr[pos_beg]))
        pos_beg++;
        else
        {
        if(('0'==string_ptr[pos_beg])&&(('x'==string_ptr[pos_beg+1])||('X'==string_ptr[pos_beg+1])))
            pos_beg+=2;
        }
    if(pos_beg>pos_end)
        return -F247_PARSE01_ERR_invalid;
    if(pos_beg+7<pos_end)
        return -F247_PARSE01_ERR_datarange;
    for(;pos_beg<=pos_end;pos_beg++)
        {
        (*data_ptr)<<=4;
        switch(string_ptr[pos_beg])
            {
            case 'a' ... 'f':
                (*data_ptr)|=(U32)(string_ptr[pos_beg]-'a'+10);
                break;
            case 'A' ... 'F':
                (*data_ptr)|=(U32)(string_ptr[pos_beg]-'A'+10);
                break;
            case '0' ... '9':
                (*data_ptr)|=(U32)(string_ptr[pos_beg]-'0');
                break;
            default:
                return -F247_PARSE01_ERR_invalid;
            }
        }
    return -F247_PARSE01_ERR_ok;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



int F247_PARSE01_get_double(F247_PARSE01_char* string_ptr, double* data_ptr)
#if __INCLUDE_LEVEL__ == 0
    {
    double temp;
    if(1!=sscanf(string_ptr,"%lf",&temp))
        return -F247_PARSE01_ERR_invalid;
    *data_ptr=temp;
    return -F247_PARSE01_ERR_ok;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0



/* - - - - - - - ------------------------------ - - - - - - - - - - - - */ 

#endif /* __F247_PARSE01_CPP__ */

