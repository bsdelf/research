import web

render = web.template.render('templates/')

urls = (
    '/',	'index',
    '/dbrows',	'dbrows',
    '/insert',	'insert',
    '/ajax',	'ajax',
)

app = web.application(urls, globals())
application = app.wsgifunc()

class index:
    def GET(self):
	i = web.input(name=None)
	return render.index(i.name)

class dbrows:
    def GET(self):
	db = web.database(dbn="postgres", user='webpy', pw='webpyz', db="webpydata")
	rows = db.select('test')
	return render.dbrows(rows)

class insert:
    def POST(self):
	i = web.input()
	db = web.database(dbn="postgres", user='webpy', pw='webpyz', db="webpydata")
	n = db.insert('test', id=i.id, name=i.name)
	rows = db.select('test')
	raise web.seeother('/dbrows')
	return render.dbrows(rows)

my_form = web.form.Form(web.form.Textbox('', class_='textfield', id='textfield'),)

def make_text(string):
	return string

class ajax:
    def POST(self):
	form = my_form()
	form.validates()
	s = form.value['textfield']
	return make_text(s) 

    def GET(self):
	form = my_form()
	return render.ajax(form, "Your text goes here.")

if __name__ == "__main__":
    app.run()
