/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
import java.util.ArrayList;

public class Profesor {
    private String nombre;
    private String dni;
    private String email;
    /*private int num_asignaturas;
    private Asignatura[] asignaturas = new Asignatura[num_asignaturas];*/
    private ArrayList asignaturas;

    public Profesor(String nombre, String dni, String email/*, int num_asignaturas*/) {
        this.nombre = nombre;
        this.dni = dni;
        this.email = email;
        /*this.num_asignaturas = num_asignaturas;*/
        asignaturas = new ArrayList();
    }
    
    public void addAsignatura(Asignatura a){
        asignaturas.add(a);
    }

    
    public ArrayList getAsignaturas(){
        return asignaturas;
    }
    
    
}
