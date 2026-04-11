import streamlit as st
import pandas as pd

st.title("Streamlit text input")
name=st.text_input("Enter your name: ")
if name :
    st.write(f"Hello {name}")

age=st.slider("What's your age ?",1,100,22)
st.write(f"Your age : {age}")

options=['C','Java','Python','Javascript']
choice=st.selectbox("Choose your favourite language :",options=options,index=1)
st.write(f"Your favourite language is : {choice}")

data=pd.DataFrame({
    'Name':['Alice','Bob','Charlie','David'],
    'Age':[24,30,22,35],
    'City':['New York','Los Angeles','Chicago','Houston']
})

st.write(data)

uploaded_file=st.file_uploader("Upload a CSV file",type=['csv'])
if uploaded_file is not None:
    df=pd.read_csv(uploaded_file)
    st.write("Uploaded CSV file:")
    st.write(df.head(10))