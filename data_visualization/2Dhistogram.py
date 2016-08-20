from sklearn.datasets import load_iris
import plotly.plotly as py
import plotly.graph_objs as go

iris = load_iris()
iris.feature_names  # print header
iris.data  # print data

x = iris.data[0:, 0:1]  # take all rows (1st indexing) of 1st column (2nd indexing)
y = iris.data[0:, 1:2]  # take all rows (1st indexing) of 2nd column (2nd indexing)

xhist = [go.Histogram(x = x, histnorm = "")]
xtitle = go.Layout(title = "Frequency Distribution of Sepal Length")
xfig = go.Figure(data = xhist, layout = xtitle)
py.plot(xfig)

yhist = [go.Histogram(x = y, histnorm = "")]
ytitle = go.Layout(title = "Frequency Distribution of Sepal Width")
yfig = go.Figure(data = yhist, layout = ytitle)
py.plot(yfig)

xyhist = [go.Histogram2d(x = x, y = y, histnorm = "")]
xytitle = go.Layout(title = "Joint Frequency Distribution of Sepal Length and Width", 
					xaxis = dict(title = "Length"),
					yaxis = dict(title = "Width"))
xyfig = go.Figure(data = xyhist, layout = xytitle)
py.plot(xyfig)
