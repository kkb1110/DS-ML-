import streamlit as st  
import pandas as pd
import numpy as np

## Title of the application
st.title("Hello World!")

### Display a simple text
st.write("This is a simple text")

df=pd.DataFrame({
    '1st column':[1,2,3,4,5],
    '2nd column':[10,20,30,40,50]
})

#Display dataframe
st.write("Here is the dataframe")
st.write(df)

data=pd.DataFrame(np.random.randn(20,3),columns=['a','b','c'])

st.line_chart(data)

#######