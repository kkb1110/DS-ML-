

let arr=[
    {"name":"Krish","gender":"Male"},
    {"name":"Sanu","gender":"M"},
    {"name":"Sangita","gender":"Female"}
]
let ans =arr.filter(elem=>{
    return (elem.gender.toLowerCase()=="male" || elem.gender.toLowerCase()=="m")
});
console.log(arr,ans)
console.log(ans[0].name.toLowerCase())
console.log(ans[1].name.toLowerCase())

