t <!DOCTYPE html>
t  <html>
t   <head>
t    <meta content="text/html; charset=UTF-8" http-equiv="content-type">
#		-------------------------------------------------------------------------------->	OJO QUE HAY QUE PONER LA URL CORRECTA:
t     <meta http-equiv="refresh" content="20; url=http://192.168.1.120/index.cgi">
t      <title>ESTACION METEOROLOGICA</title>
t       </head>
t        <body style="background-color:rgb(200,200,200);">
t          <h1 align="center">Estacion meteorologica</h1>
t           <br />
t           <table align="center" border="1">
t             <caption>Datos medios actuales:</caption>
t               <tr>
t                 <td>Temperatura:</td>
t                 <td>
c t               " %f 
t                 </td>
t                 <td>Velocidad del viento:</td>
t                 <td>
c v               " %f
t                 </td>
t               </tr>
t               <tr>
t                 <td>Humedad:</td>
t                 <td>
c h               " %f 
t                 </td>
t                 <td>Indice UV:</td>
t                 <td>
c i               " %f 
t                 </td>
t               </tr>
t               <tr>
t                 <td>Presion:</td>
t                 <td>
c p               " %f 
t                 </td>
t                 <td>Brillo:</td>
t                 <td>
c b               " %f 
t                 </td>
t               </tr>
t           </table>
t           <table align="center" border="1">
t            <tr>
t            <td>Altitud:</td>
t            <td>
c a          " %f 
t            </td>
t            <td>Longitud:</td>
t            <td>
c x          " %f 
t            </td>
t            <td>Latitud:</td>
t            <td>
c y          " %f 
t            </td>
t            </tr>
t           </table>
t           <br></br>
t           <table align="center" border="1">
t            <caption>Hora de la ultima muestra:</caption>
t            <tr>
t             <td>Anyo:</td>
t             <td>
c A           " %d
t             </td>
t             <td>Mes:</td>
t             <td>
c M           " %d
t             </td>
t             <td>Dia:</td>
t             <td>
c D           " %d
t             </td>
t            <tr>
t             <td>Hora:</td>
t             <td>
c H           " %d
t             </td>
t             <td>Minuto:</td>
t             <td>
c T           " %d
t             </td>
t             <td>Segundos:</td>
t             <td>
c S           " %d
t             </td>
t            </tr>
t           </table>
t           <br></br>
t           <br></br>
t           <table stile="width: 100%" border="1" align="center">
t            <tbody>
t             <tr>
t              <td>
t               <h1 style=" text-align: center;"> Magnitudes modificables: </h1>
t               <form method="GET" action="index.cgi">
t                <br> Temperatura min. :
t                <input size="10" value="-10" name="tmin" type="text"> 
t                <br> Temperatura max. :
t                <input size="10" value="50" name="tmax" type="text">
t                <br> Presion min. :
t                <input size="10" value="500" name="pmin" type="text">
t                <br> Presion max. :
t                <input size="10" value="1500" name="pmax" type="text">
t                <br> Segundos encendido :
t                <input size="10" value="10" name="bsec" type="text">
t                <br> <input value="si" type="radio" name="vart"> Temperatura<br>
t                <input value="si" type="radio" name="varp"> Presion<br>
t                <br> <input value="Enviar" type="submit">
t               </form>
t              </td>
t             </tr>
t            </tbody>
t           </table>
t           <br></br>
t           <br></br>
t           <br></br>
t           <br></br>
t           <table align="center">
t            <tr>
t             <td>Autor:	Alberto Palomo Alonso.</td>
t             <td>Sistemas Electronicos Digitales Avanzados.</td>
t             <td>Universidad de Alcala - Escuela politecnica superior.</td>
t            </tr>
t           </table>
t       </body>
t   </html>
.