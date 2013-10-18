About
---------------
**bwlogd** logs average bandwidth usage over an interval. It is meant to be tiny, efficient, and simple - ideally to have no noteworthy impact on a system.

bwlogd does not require root, and can be run as the *nobody* user.

An html/javascript graph viewer is included under *www/*.

Options
---------------
`-i` Interface to monitor, defaults to eth0

`--interval` Interval (seconds) between updates, defaults to 60

Examples
---------------
**Convert Output to JSON**

`bwlogd | while read line; do line=($line); echo ",['${line[0]}','${line[1]}', '${line[2]}']"; done`

**Log Output to File by Date**

`bwlogd | while read line; do echo "$line" >> $(date +%Y-%m-%d).log; done`

**Send Output to Syslog**

`bwlogd | logger -t bwlogd`
(See the man pages for `logger` or your syslog daemon for more detail on using syslog)

Build/Installation
---------------
Build: `make`

Install: `make install`

**bwlogd** links to [libstatgrab](https://github.com/i-scream/libstatgrab). On a debian or ubuntu system, you can simply `apt-get install libstatgrab-dev` to install the required files.


License ![CC0](https://i.creativecommons.org/p/zero/1.0/80x15.png)
---------------
To the extent possible under law, the author has waived all copyright and related or neighbouring rights to this software. 

>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
