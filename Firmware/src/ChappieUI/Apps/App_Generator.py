import os as os
from shutil import copyfile


app_name = ""
def getAppName():
    global app_name
    app_name = input("> Please input your App name: ")


def creteApp():
    # Get file name
    folder_name = "App_" + app_name
    source_file_name = "App_" + app_name + "/App_" + app_name + ".cpp"
    header_file_name = "App_" + app_name + "/App_" + app_name + ".h"
    print("> File names:\n - {}\n - {}\n".format(source_file_name, header_file_name))

    # Create folder
    os.mkdir(folder_name)

    # Create files 
    source_file = open(source_file_name, mode='x')
    header_file = open(header_file_name, mode='x')

    # Read Template content
    content_source_file = open("Resource/App_Template/App_Template.cpp", mode='r').read()
    content_header_file = open("Resource/App_Template/App_Template.h", mode='r').read()

    # Rename
    content_source_file = content_source_file.replace("Template", app_name)
    content_header_file = content_header_file.replace("Template", app_name)
    
    # Enable
    content_source_file = content_source_file.replace("#if 0", "#if 1")
    content_header_file = content_header_file.replace("#if 0", "#if 1")

    # Write in
    source_file.write(content_source_file)
    header_file.write(content_header_file)

    # Close files
    source_file.close()
    header_file.close()

    # print("> Add them to your \"AppRegister.h\" :\n")
    # print("#include \"App_{}/App_{}.h\"".format(app_name, app_name))
    # print("App_Login({}),".format(app_name))


def loginApp():
    # Open AppRegister.h and read current contents
    register_file = open("AppRegister.h", mode='r')
    content_register_file = register_file.read()
    register_file.close()

    # Add including
    content_register_file = content_register_file.replace("/* Header files locator */", "#include \"App_{}/App_{}.h\"\n/* Header files locator */".format(app_name, app_name))
    
    # Add App login
    content_register_file = content_register_file.replace("/* Login locator */", "App_Login({}),\n\t\t/* Login locator */".format(app_name))

    # print(content_register_file)
    
    # Open AppRegister.h and cover
    register_file = open("AppRegister.h", mode='w+')
    register_file.write(content_register_file)
    register_file.close()

    print("> App Loged in register")


if __name__=="__main__":
    print("> ChappieUI App generator <")
    
    while True:
        getAppName()
        if app_name != "":
            break
        print("X Error name, please try again\n")
    print("> Get App name: {}\n".format(app_name))
    
    creteApp()

    loginApp()

    print("\n> Done <")

