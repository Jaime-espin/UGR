/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gestortareas;

/**
 *
 * @author Jaime Espín
 */
public class TareaTrabajo extends Tarea{

    public TareaTrabajo(String titulo, String descripcion, Prioridad prioridad) {
        super(titulo, descripcion, prioridad);
    }

    @Override
    public String mostrarDetalles() {
        return super.getTitulo()+" "+super.getDescripcion();
    }

    @Override
    public TipoTarea getCategoria() {
        return TipoTarea.TRABAJO;
    }
    
    
    
}
