#define ASSERT_STACK( expression ) \
if (expression) {\
\
} else {\
FILE *files = fopen ("LogFiles.txt", "at");\
\
fprintf(files, "==========ASSERT_STACK=========\n\n");\
fprintf(files, "ERROR:\nAssertion failed: %s\n   in file %s;\n   in line %i.\n", #expression, __FILE__, __LINE__);\
fprintf(files, "\n===========================\n\n");\
\
fclose(files);\
assert (expression);\
}

template <typename data_T>

class stackmy
{
public:
    stackmy ();
    ~stackmy ();
    
    data_T  pop ();
    data_T  top ();
    
    bool    push (data_T val);
    
    size_t  size ();
    
    bool    check ();
    
    void    dump ();
    
private:
    int  _size;
    int  _capacity;
    
    data_T*  _data;
    char* _LOG_FILES_NAME = "LogFilesStack.txt";
    
    bool    _resize (size_t new_sz);
    bool    Dump   ();
};

template <typename data_T>
stackmy <data_T> :: stackmy () :
_size (0),
_capacity (1),
_data (nullptr)
{
    _size = 0;
    _capacity = 1;
    _data = new data_T [_capacity] {NULL};
    ASSERT_STACK(_data)
};

template <typename data_T>
stackmy <data_T> :: ~stackmy ()
{
    if (_data != nullptr)
        delete _data;
};

template <typename data_T>
data_T stackmy <data_T> :: pop ()
{
    //Dump ();
    if (_size > 0)
    {
        _size--;
        return _data [_size];
    }
    return NULL;
}

template <typename data_T>
data_T stackmy <data_T> :: top ()
{
    if (_size > 0)
        return _data [_size - 1];
};

template <typename data_T>
bool stackmy <data_T> :: push (data_T val)
{
    if (_size >= _capacity)
    {
        _resize (_capacity * 2);
        _capacity *= 2;
    }
    
    _data[_size++] = val;
    //Dump ();
    return 0;
    
}

template <typename data_T>
size_t stackmy <data_T> :: size ()
{
    return _size;
}

template <typename data_T>
bool stackmy <data_T> :: _resize (size_t new_sz)
{
    data_T* newdata = new data_T [new_sz] {NULL};
    ASSERT_STACK(newdata)
    for (int i = 0; i < _size; i++)
        newdata [i] = _data [i];
    
    delete _data;
    _data = newdata;
    return 0;
}

template <typename data_T>
bool stackmy <data_T> :: Dump ()
{
    FILE *files = fopen (_LOG_FILES_NAME, "at");
    assert(files);
    
    fprintf(files, "==========stackmy==========\n\n");
    
    
    fprintf (files, "_size = %i\n\n", _size);
    fprintf (files, "_capacity = %i\n\n", _capacity);
    
    for (int i = 0; i < _size; i++) {
        fprintf(files, "_data[%i] = %i\n", i, _data [i]);
    }
    
    fprintf(files, "\n===========================\n\n");
    
    fclose(files);
    return 0;
}

#undef ASSERT_STACK
