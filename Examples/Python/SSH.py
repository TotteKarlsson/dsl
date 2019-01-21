import base64
import getpass
import os
import socket
import sys
import traceback
from paramiko.py3compat import input

import paramiko

##try:
##    import interactive
##except ImportError:
##    from . import interactive


# setup logging
paramiko.util.log_to_file("demo_simple.log")
# Paramiko client configuration
UseGSSAPI = (
    paramiko.GSS_AUTH_AVAILABLE
)  # enable "gssapi-with-mic" authentication, if supported by your python installation
DoGSSAPIKeyExchange = (
    paramiko.GSS_AUTH_AVAILABLE
)  # enable "gssapi-kex" key exchange, if supported by your python installation
# UseGSSAPI = False
# DoGSSAPIKeyExchange = False
port = 22

# get hostname
username = "totte"
hostname = "atbigdawg"
password = "lacket47"
# now, connect and use paramiko Client to negotiate SSH2 across the connection
try:
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    client.set_missing_host_key_policy(paramiko.WarningPolicy())
    print("*** Connecting...")
    if not UseGSSAPI and not DoGSSAPIKeyExchange:
        client.connect(hostname, port, username, password)
    else:
        try:
            client.connect(
                hostname,
                port,
                username,
                gss_auth=UseGSSAPI,
                gss_kex=DoGSSAPIKeyExchange,
            )
        except Exception:
            # traceback.print_exc()
            password = "lacket47"
            client.connect(hostname, port, username, password)

    chan = client.invoke_shell()
    chan.send("ls -all")
    print(repr(client.get_transport()))
    print("*** Here we go!\n")
    #interactive.interactive_shell(chan)
    chan.close()
    client.close()

except Exception as e:
    print("*** Caught exception: %s: %s" % (e.__class__, e))
    traceback.print_exc()
    try:
        client.close()
    except:
        pass
    sys.exit(1)