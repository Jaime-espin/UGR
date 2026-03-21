/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
public class Alumno {
    private String nombre;
    private String dni;
    private String email;

    public Alumno(String nombre, String dni, String email) {
        this.nombre = nombre;
        this.dni = dni;
        this.email = email;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public void setEmail(String email) {
        if(Correcto(email)){
            this.email = email;
        }
    }
    
    public boolean Correcto(String email){
        //Devuelve si el correo dado tiene un formato correcto
        return true;
    }
    
}
